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

bool DatabaseManager::createTables() const
{
    QSqlQuery query;
    QString queryText;

    queryText = "CREATE TABLE IF NOT EXISTS teachers ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "fullName TEXT)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы преподавателей: "
                 << query.lastError();
        return false;
    }

    queryText = "CREATE TABLE IF NOT EXISTS groups ("
                "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
                "name TEXT)";
    if (!query.exec(queryText)) {
        qDebug() << "Ошибка при создании таблицы групп: "
                 << query.lastError();
        return false;
    }

    return true;
}

bool DatabaseManager::insertToTeachers(const QString &fullName) const
{
    QSqlQuery query;
    query.prepare("INSERT INTO teachers (fullName) VALUES (:name)");
    query.bindValue(":name", fullName);
    if (!query.exec()) {
        qDebug() << "Ошибка при вставке в teachers"
                 << query.lastError();
        return false;
    }

    qDebug() << "Строка успешно вствлена в teachers";
    return true;
}

bool DatabaseManager::insertToGroups(const QString &name) const
{
    if (isItemInGroups(name))
        return false;

    QSqlQuery query;
    query.prepare("INSERT INTO groups (name) VALUES (:name)");
    query.bindValue(":name", name);
    if (!query.exec()) {
        qDebug() << "Ошибка при вставке в groups"
                 << query.lastError();
        return false;
    }

    qDebug() << "Строка успешно вствлена в groups";
    return true;
}

QStringList DatabaseManager::selectFromTeachers() const
{
    QSqlQuery query;
    if (!query.exec("SELECT fullName FROM teachers")) {
        qDebug() << "Ошибка при получении данных из teachers"
                 << query.lastError();
        return QStringList();
    }

    QStringList result;
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    result.sort();
    return result;
}

QStringList DatabaseManager::selectFromGroups() const
{
    QSqlQuery query;
    if (!query.exec("SELECT name FROM groups")) {
        qDebug() << "Ошибка при получении данных из groups"
                 << query.lastError();
        return QStringList();
    }

    QStringList result;
    while (query.next()) {
        result.append(query.value(0).toString());
    }
    result.sort();
    return result;
}

bool DatabaseManager::deleteFromTeachers(const QString &item) const
{
    return false;
}

bool DatabaseManager::deleteFromGroups(const QString &item) const
{
    QSqlQuery query;
    query.prepare("DELETE FROM groups WHERE name = :item");
    query.bindValue(":item", item);
    if (!query.exec()) {
        qDebug() << "Ошибка при удалении элемента из таблицы groups:"
                 << query.lastError();
        return false;
    }
    return true;
}

bool DatabaseManager::isItemInTeachers(const QString &item) const
{
    return false;
}

bool DatabaseManager::isItemInGroups(const QString &item) const
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(name) FROM groups WHERE name = :item");
    query.bindValue(":item", item);
    if (!query.exec()) {
        qDebug() << "Ошибка при получении кол-ва эл-тов из groups"
                 << query.lastError();
        return true;
    }

    int count = query.next() ? query.value(0).toInt() : 0;
    return count > 0;
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

QSqlDatabase *DatabaseManager::database()
{
    return &m_db;
}
