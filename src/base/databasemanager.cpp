#include "databasemanager.h"

#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QDate>

Q_GLOBAL_STATIC(DatabaseManager, databaseManagerInstance)

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    m_db.close();
}

DatabaseManager *DatabaseManager::instance()
{
    return databaseManagerInstance;
}

void DatabaseManager::setUserId(int id)
{
    m_userId = id;
}

bool DatabaseManager::connect()
{
    QString dbPath = "database.db";
    m_db = QSqlDatabase::addDatabase("SQLITECIPHER");
    m_db.setDatabaseName(dbPath);
    m_db.setPassword("supersecretpassword");

    if (!m_db.open()) {
        qDebug() << "Ошибка при открытии БД:"
                 << m_db.lastError().text();
        return false;
    }

    if (!createTables())
        return false;

    return true;
}

bool DatabaseManager::insertToUsers(const QString &login,
                                    const QByteArray &password,
                                    const QByteArray &salt) const
{
    QVariantMap data;
    data["login"] = login;
    data["password"] = password;
    data["salt"] = salt;

    return insertIntoTable("users", data);
}

bool DatabaseManager::insertToGroups(const QString &item) const
{
    if (isItemInTable(item, "groups", "name"))
        return false;

    QVariantMap data;
    data["name"] = item;
    data["user_id"] = m_userId;
    return insertIntoTable("groups", data);
}

bool DatabaseManager::insertToSubjects(const QString &item) const
{
    if (isItemInTable(item, "subjects", "name"))
        return false;

    QVariantMap data;
    data["name"] = item;
    data["user_id"] = m_userId;
    return insertIntoTable("subjects", data);
}

bool DatabaseManager::insertToStudents(const QString &item,
                                       int groupId) const
{
    QVariantMap data;
    data["name"] = item;
    data["group_id"] = groupId;
    return insertIntoTable("students", data);
}

bool DatabaseManager::insertToAbsentees(int group_id,
                                        const QDate &date,
                                        const QString &names)
{
    QVariantMap data;
    data["user_id"] = m_userId;
    data["group_id"] = group_id;
    data["date"] = date;
    data["name"] = names;
    return insertIntoTable("absentees", data);
}

QStringList DatabaseManager::selectNamesFromGroups() const
{
    QString condition = QString("user_id = %1").arg(m_userId);
    QSqlQuery query = selectFromTable("groups", condition);
    return stringListByQuery(query, "name");
}

int DatabaseManager::selectIdFromGroups(const QString &groupName) const
{
    QString condition = QString("user_id = %1 AND name = '%2'")
                            .arg(QString::number(m_userId), groupName);
    QSqlQuery query = selectFromTable("groups", condition);
    return query.next() ? query.value("id").toInt() : -1;
}

QString DatabaseManager::selectNameFromGroups(int groupId) const
{
    QString condition = QString("id = %1").arg(groupId);
    QSqlQuery query = selectFromTable("groups", condition);
    return query.next() ? query.value("name").toString() : QString();
}

QStringList DatabaseManager::selectNamesFromSubjects() const
{
    QString condition = QString("user_id = %1").arg(m_userId);
    QSqlQuery query = selectFromTable("subjects", condition);
    return stringListByQuery(query, "name");
}

QVariantMap DatabaseManager::selectRowFromUsers(const QString &login) const
{
    QVariantMap result;
    QString condition = QString("login = '%1'").arg(login);
    QSqlQuery query = selectFromTable("users", condition);
    if (!query.next())
        return result;

    result["id"] = query.value("id").toInt();
    result["login"] = query.value("login").toString();
    result["password"] = query.value("password").toByteArray();
    result["salt"] = query.value("salt").toByteArray();

    return result;
}

int DatabaseManager::selectIdFromUsers(const QString &login) const
{
    QString condition = QString("login = '%1'").arg(login);
    QSqlQuery query = selectFromTable("users", condition);
    if (!query.next())
        return -1;

    return query.value("id").toInt();
}

QByteArray DatabaseManager::selectPasswordFromUsers(const QString &login) const
{
    QByteArray result;
    QString condition = QString("login = '%1'").arg(login);
    QSqlQuery query = selectFromTable("users", condition);
    if (!query.next())
        return result;

    return query.value("password").toByteArray();
}

QByteArray DatabaseManager::selectSaltFromUsers(const QString &login) const
{
    QByteArray result;
    QString condition = QString("login = '%1'").arg(login);
    QSqlQuery query = selectFromTable("users", condition);
    if (!query.next())
        return result;

    return query.value("salt").toByteArray();
}

QStringList DatabaseManager::selectNamesFromStudents(int groupId) const
{
    QString condition = QString("group_id = %2").arg(groupId);
    QSqlQuery query = selectFromTable("students", condition);
    return stringListByQuery(query, "name");
}

QList<QDate> DatabaseManager::selectDatesFromAbsentees() const
{
    QList<QDate> result;
    QSqlQuery query;
    QString queryText = QString("SELECT DISTINCT date FROM absentees "
                                "WHERE user_id = %1").arg(m_userId);
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при выборе дат:"
                 << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(query.value(0).toDate());
    }
    return result;
}

QStringList DatabaseManager::selectNamesFromAbsentees(const QDate &date,
                                                      int groupId)
{
    QString dateString = date.toString(Qt::ISODate);
    QString condition = QString("date = '%1' AND group_id = %2")
                            .arg(dateString).arg(groupId);
    QSqlQuery query = selectFromTable("absentees", condition);
    QStringList result;
    while (query.next()) {
        result.append(query.value("name").toString());
    }

    return result;
}

QList<int> DatabaseManager::selectGroupIdFromAbsentees(const QDate &date)
{
    QString dateString = date.toString(Qt::ISODate);
    QString condition = QString("date = '%1' AND user_id = %2")
                            .arg(dateString).arg(m_userId);
    QSqlQuery query = selectFromTable("absentees", condition);
    QList<int> result;
    while (query.next()) {
        result.append(query.value("group_id").toInt());
    }

    return result;
}

QHash<int, QStringList> DatabaseManager::selectFromAbsentees(const QDate &date)
{
    QSqlQuery query;
    QList<int> groupsId;
    QHash<int, QStringList> result;
    QString dateString = date.toString(Qt::ISODate);
    QString queryText = QString("SELECT DISTINCT group_id FROM absentees "
                                "WHERE date = '%1'").arg(dateString);
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при получении индексов групп"
                 << query.lastError();
        return result;
    }

    while (query.next()) {
        groupsId.append(query.value(0).toInt());
    }

    for (int groupId : groupsId) {
        result[groupId] = selectNamesFromAbsentees(date, groupId);
    }

    return result;
}

bool DatabaseManager::deleteFromGroups(const QString &item) const
{
    QString condition = QString("name = '%1' AND user_id = %2")
                            .arg(item).arg(m_userId);
    return deleteFromTable("groups", condition);
}

bool DatabaseManager::deleteFromSubjects(const QString &item) const
{
    QString condition = QString("name = '%1' AND user_id = %2")
                            .arg(item).arg(m_userId);
    return deleteFromTable("subjects", condition);
}

bool DatabaseManager::deleteFromStudents(const QString &item, int groupId) const
{
    QString condition = QString("name = '%1' AND group_id = %2")
                            .arg(item).arg(groupId);
    return deleteFromTable("students", condition);
}

bool DatabaseManager::deleteFromAbsentees(const QDate &date)
{
    QString dateString = date.toString(Qt::ISODate);
    QString condition = QString("date = '%1' AND user_id = %2")
                            .arg(dateString).arg(m_userId);
    return deleteFromTable("absentees", condition);
}

QSqlDatabase *DatabaseManager::database()
{
    return &m_db;
}

bool DatabaseManager::createDatabaseFile(const QString &path) const
{
    if (!QFile::exists(path)) {
        QFile file(path);
        if (!file.open(QFile::ReadWrite)) {
            qDebug() << "Ошибка при создании файла БД";
            return false;
        }
    }

    return true;
}

bool DatabaseManager::createTables() const
{
    QSqlQuery query;
    QString queryText;

    queryText = "PRAGMA foreign_keys = ON";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при включении внешних ключей: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS users ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "login TEXT NOT NULL UNIQUE,"
                "password BINARY(32) NOT NULL,"
                "salt BINARY(16) NOT NULL)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы пользователей: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS groups ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "user_id INTEGER NOT NULL REFERENCES users(id),"
                "name TEXT NOT NULL)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы групп: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS subjects ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "user_id INTEGER NOT NULL REFERENCES users(id),"
                "name TEXT NOT NULL)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы дисциплин: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS students ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "group_id INTEGER NOT NULL REFERENCES groups(id) ON DELETE CASCADE,"
                "name TEXT NOT NULL)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы учеников: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS absentees ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "user_id INTEGER NOT NULL REFERENCES users(id),"
                "group_id INTEGER NOT NULL REFERENCES groups(id),"
                "date DATE NOT NULL,"
                "name TEXT)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы отсутствующих: "
                 << query.lastError();
        return false;
    }

    return true;
}

QStringList DatabaseManager::stringListByQuery(QSqlQuery &query,
                                               const QString &column) const
{
    QStringList result;
    while (query.next()) {
        result.append(query.value(column).toString());
    }

    return result;
}

bool DatabaseManager::insertIntoTable(const QString &table,
                                      const QVariantMap &data) const
{
    QSqlQuery query;
    QString queryText;
    QStringList columns;
    QStringList paramNames;

    columns = data.keys();
    for (const QString &column : columns) {
        paramNames.append(":" + column);
    }

    queryText = QString("INSERT INTO %1 (%2) VALUES (%3)")
                    .arg(table,
                         columns.join(", "),
                         paramNames.join(", "));
    query.prepare(queryText);
    for (const QString &column : columns) {
        query.bindValue(":" + column, data[column]);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка при вставке в таблицу " << table
                 << query.lastError();
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::selectFromTable(const QString &table,
                                           const QString &condition) const
{
    QSqlQuery query;
    QString queryText;

    queryText = "SELECT * FROM " + table;
    if (!condition.isEmpty()) {
        queryText += " WHERE " + condition;
    }

    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при выборке из таблицы " << table
                 << query.lastError();
    }

    return query;
}

bool DatabaseManager::deleteFromTable(const QString &table,
                                      const QString &condition) const
{
    QSqlQuery query;
    QString queryText;

    queryText = QString("DELETE FROM %1 WHERE %2").arg(table, condition);
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при удалении из " << table
                 << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::isItemInTable(const QString &item,
                                    const QString &table,
                                    const QString &column,
                                    bool checkUserId) const
{
    QSqlQuery query;
    QString queryText;
    queryText = QString("SELECT COUNT(*) FROM %1 WHERE %2 = :item").arg(table, column);
    if (checkUserId) {
        queryText += QString(" AND user_id = '%1'").arg(m_userId);
    }
    query.prepare(queryText);
    query.bindValue(":item", item);
    if (!query.exec()) {
        qDebug() << "Ошибка при получении кол-ва эл-тов из "
                 << table
                 << query.lastError();
        return true;
    }

    int count = query.next() ? query.value(0).toInt() : 0;
    return count > 0;
}
