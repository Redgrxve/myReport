#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager &dm) = delete;
    DatabaseManager &operator=(const DatabaseManager &dm) = delete;

    static DatabaseManager *instance();

    void setUserId(int id);

    bool connect();

    bool insertToUsers(const QString &login,
                       const QByteArray &password,
                       const QByteArray &salt) const;
    bool insertToGroups(const QString &item) const;
    bool insertToSubjects(const QString &item) const;
    bool insertToStudents(const QString &item,
                          int groupId) const;
    bool insertToAbsentees(int group_id,
                           const QDate &date,
                           const QString &names);

    QStringList selectNamesFromGroups() const;
    int selectIdFromGroups(const QString &groupName) const;
    QString selectNameFromGroups(int groupId) const;
    QStringList selectNamesFromSubjects() const;
    int selectIdFromSubjects(const QString &name) const;
    QVariantMap selectRowFromUsers(const QString &login) const;
    int selectIdFromUsers(const QString &login) const;
    QByteArray selectPasswordFromUsers(const QString &login) const;
    QByteArray selectSaltFromUsers(const QString &login) const;
    QStringList selectNamesFromStudents(int groupId) const;
    QList<QDate> selectDatesFromAbsentees() const;
    QStringList selectNamesFromAbsentees(const QDate &date,
                                         int groupId);
    QList<int> selectGroupIdFromAbsentees(const QDate &date);
    QHash<int, QStringList> selectFromAbsentees(const QDate &date);


    bool deleteFromGroups(const QString &item) const;
    bool deleteFromSubjects(const QString &item) const;
    bool deleteFromStudents(const QString &item, int groupId) const;
    bool deleteFromAbsentees(const QDate &date);

    bool isItemInAbsentees(const QDate &date);

    QSqlDatabase *database();

private:
    QSqlDatabase m_db;
    int m_userId;

    bool createDatabaseFile(const QString &path) const;
    bool createTables() const;

    QStringList stringListByQuery(QSqlQuery &query,
                                  const QString &column) const;

    bool insertIntoTable(const QString &table,
                         const QVariantMap &data) const;

    QSqlQuery selectFromTable(const QString &table,
                              const QString &condition = "") const;

    bool deleteFromTable(const QString &table,
                         const QString &condition) const;

    bool isItemInTable(const QVariant &item,
                       const QString &table,
                       const QString &column,
                       const QString &additionalCondition = "",
                       bool checkUserId = true) const;
};

#endif // DATABASEMANAGER_H
