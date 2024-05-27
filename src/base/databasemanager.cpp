#include "databasemanager.h"

#include <QStringList>
#include <QFile>
#include <QDebug>

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

bool DatabaseManager::connect()
{
    QString dbPath = "database.db";
    m_db = QSqlDatabase::addDatabase("SQLITECIPHER");
    m_db.setDatabaseName(dbPath);
    //m_db.setPassword("supersecretpassword");

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
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password, salt)"
                  "VALUES (:login, :password, :salt)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    query.bindValue(":salt", salt);
    if (!query.exec()) {
        qDebug() << "Ошибка при вствке в users: "
                 << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::insertToGroups(const QString &item) const
{
    return insertToTable(item, "groups", "name");
}

bool DatabaseManager::insertToSubjects(const QString &item) const
{
    return insertToTable(item, "subjects", "name");
}

QStringList DatabaseManager::selectFromGroups() const
{
    return selectFromTable("groups", "name");
}

QStringList DatabaseManager::selectFromSubjects() const
{
    return selectFromTable("subjects", "name");
}

int DatabaseManager::selectIdFromUsers(const QString &login) const
{
    return selectFromUsersByLogin(login, "id").toInt();
}

QByteArray DatabaseManager::selectPasswordFromUsers(const QString &login) const
{
    return selectFromUsersByLogin(login, "password");
}

QByteArray DatabaseManager::selectSaltFromUsers(const QString &login) const
{
    return selectFromUsersByLogin(login, "salt");
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
                "name TEXT NOT NULL,"
                "UNIQUE(name))";
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

// not working
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

QByteArray DatabaseManager::selectFromUsersByLogin(const QString &login,
                                                   const QString &column) const
{
    QByteArray result;
    if (!isItemInTable(login, "users", "login"))
        return result;

    QSqlQuery query;
    QString queryText = QString("SELECT %1 FROM users WHERE login = :login")
        .arg(column);
    query.prepare(queryText);
    query.bindValue(":login", login);
    if (!query.exec())
        return result;

    result = query.next() ? query.value(0).toByteArray() : "";
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
