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

    bool insertToTeachers(const QString &item) const;
    bool insertToGroups(const QString &item) const;
    bool insertToDisciplines(const QString &item) const;

    QStringList selectFromTeachers() const;
    QStringList selectFromGroups() const;
    QStringList selectFromDisciplines() const;

    bool deleteFromTeachers(const QString &item) const;
    bool deleteFromGroups(const QString &item) const;
    bool deleteFromDisciplines(const QString &item) const;

    QSqlDatabase *database();

private:
    DatabaseManager();
    ~DatabaseManager();

    static DatabaseManager *m_instance;

    QSqlDatabase m_db;

    bool createDatabaseFile(const QString &path) const;
    bool createTables() const;

    bool insertToTable(const QString &item,
                       const QString &table,
                       const QString &column) const;

    QStringList selectFromTable(const QString &table,
                                const QString &column) const;

    bool deleteFromTable(const QString &item,
                         const QString &table,
                         const QString &column) const;

    bool isItemInTable(const QString &item,
                       const QString &table,
                       const QString &column) const;
};

#endif // DATABASEMANAGER_H
