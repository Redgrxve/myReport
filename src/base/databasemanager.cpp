#include "databasemanager.h"
#include "qdebug.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QFile>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {}

DatabaseManager *DatabaseManager::instance()
{
    if (!m_instance)
        m_instance = new DatabaseManager;

    return m_instance;
}

bool DatabaseManager::connect()
{
    QString dbPath = "database.db";
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!createDatabaseFile(dbPath))
        return false;

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
                                    const QString &password) const
{
    return insertToTable({login, password}, "users", {"login", "password"});
}

bool DatabaseManager::insertToGroups(const QString &item) const
{
    return insertToTable(item, "groups", "name");
}

bool DatabaseManager::insertToSubjects(const QString &item) const
{
    return insertToTable(item, "subjects", "name");
}

QStringList DatabaseManager::selectFromTeachers() const
{
    return selectFromTable("teachers", "fullName");
}

QStringList DatabaseManager::selectFromGroups() const
{
    return selectFromTable("groups", "name");
}

QStringList DatabaseManager::selectFromSubjects() const
{
    return selectFromTable("subjects", "name");
}

QString DatabaseManager::selectPasswordFromUsers(const QString &login) const
{
    QString result;
    if (!isItemInTable(login, "users", "login"))
        return result;

    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE login = :login");
    query.bindValue(":login", login);
    if (!query.exec())
        return result;

    result = query.next() ? query.value(0).toString() : "";
    return result;
}

bool DatabaseManager::deleteFromTeachers(const QString &item) const
{
    return deleteFromTable(item, "teachers", "fullName");
}

bool DatabaseManager::deleteFromGroups(const QString &item) const
{
    return deleteFromTable(item, "groups", "name");
}

bool DatabaseManager::deleteFromSubjects(const QString &item) const
{
    return deleteFromTable(item, "subjects", "name");
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

    queryText = "CREATE TABLE IF NOT EXISTS users ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "login TEXT NOT NULL,"
                "password TEXT NOT NULL,"
                "UNIQUE(login))";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы пользователей: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS groups ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL,"
                "UNIQUE(name))";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы групп: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS subjects ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT NOT NULL)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы дисциплины: "
                 << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::insertToTable(const QString &item,
                                    const QString &table,
                                    const QString &column) const
{
    QSqlQuery query;
    QString queryText;

    queryText = QString("INSERT INTO %1 (%2) VALUES (:item)")
                    .arg(table, column);
    query.prepare(queryText);
    query.bindValue(":item", item);
    if (!query.exec()) {
        qDebug() << "Ошибка при вставке в "
                 << table
                 << query.lastError();
        return false;
    }

    qDebug() << "Строка успешно вствлена в " << table;
    return true;
}

bool DatabaseManager::insertToTable(const QStringList items,
                                    const QString &table,
                                    const QStringList &columns) const
{
    if (items.size() != columns.size())
        return false;

    QSqlQuery query;
    QStringList queryParams;
    QString queryText;
    QString paramNames;
    QString columnNames;

    for (int i = 0; i < items.size(); ++i) {
        queryParams.append(":value" + QString::number(i));
    }
    paramNames = queryParams.join(", ");
    columnNames = columns.join(", ");
    queryText = QString("INSERT INTO %1 (%2) VALUES (%3)")
                    .arg(table, columnNames, paramNames);
    query.prepare(queryText);
    for (int i = 0; i < items.size(); ++i) {
        query.bindValue(queryParams[i], items[i]);
    }

    if (!query.exec()) {
        qDebug() << "Ошибка при вставке в "
                 << table
                 << query.lastError();
        return false;
    }

    return true;
}

QStringList DatabaseManager::selectFromTable(const QString &table,
                                             const QString &column) const
{
    QSqlQuery query;
    QStringList result;

    if (!query.exec("SELECT " + column + " FROM " + table)) {
        qDebug() << "Ошибка при получении данных из "
                 << table
                 << query.lastError();
        return result;
    }

    while (query.next()) {
        result.append(query.value(0).toString());
    }
    result.sort();
    return result;
}

// not usable
QStringList DatabaseManager::selectFromTable(const QString &table,
                                             const QString &column,
                                             const QString &condition) const
{
    QSqlQuery query;
    QString queryText;
    QStringList result;

    if (condition.isEmpty()) {
        queryText = QString("SELECT %1 FROM %2").arg(column, table);
    } else {
        queryText = QString("SELECT %1 FROM %2 WHERE %3")
                        .arg(column, table, condition);
    }

    if (!query.exec(queryText))
        return result;

    while (query.next()) {
        result.append(query.value(0).toString());
    }

    return result;
}

bool DatabaseManager::deleteFromTable(const QString &item,
                                      const QString &table,
                                      const QString &column) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM " + table + " WHERE "
                  + column + " = :item");
    query.bindValue(":item", item);
    if (!query.exec()) {
        qDebug() << "Ошибка при удалении элемента из "
                 << table
                 << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::isItemInTable(const QString &item,
                                    const QString &table,
                                    const QString &column) const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM " + table + " WHERE "
                  + column + " = :item");
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
