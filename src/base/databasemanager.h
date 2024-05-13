#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    DatabaseManager(const DatabaseManager &dm) = delete;
    DatabaseManager& operator=(const DatabaseManager &dm) = delete;

    static DatabaseManager *instance();

    bool connect();

    bool insertToTeachers(const QString &fullName) const;
    bool insertToGroups(const QString &name) const;

    QStringList selectFromTeachers() const;
    QStringList selectFromGroups() const;

    bool deleteFromTeachers(const QString &item) const;
    bool deleteFromGroups(const QString &item) const;

    bool isItemInTeachers(const QString &item) const;
    bool isItemInGroups(const QString &item) const;

    QSqlDatabase *database();

private:
    DatabaseManager();
    ~DatabaseManager();

    static DatabaseManager *m_instance;

    QSqlDatabase m_db;

    bool createDatabaseFile(const QString &path) const;
    bool createTables() const;
};

#endif // DATABASEMANAGER_H
