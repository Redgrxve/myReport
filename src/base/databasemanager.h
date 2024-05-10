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
    bool createDatabaseFile(const QString &path) const;
    bool createTables() const;
    bool insertToTeachers(const QString &fullName) const;
    bool insertToGroups(const QString &name) const;
    QStringList selectFromTeachers() const;
    QSqlDatabase *database();

private:
    DatabaseManager();
    ~DatabaseManager();

    static DatabaseManager *m_instance;

    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
