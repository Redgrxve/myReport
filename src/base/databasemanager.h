#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QGlobalStatic>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager &dm) = delete;
    DatabaseManager& operator=(const DatabaseManager &dm) = delete;

    static DatabaseManager *instance();

    bool connect();

    bool insertToUsers(const QString &login,
                       const QByteArray &password,
                       const QByteArray &salt) const;
    bool insertToGroups(const QString &item) const;
    bool insertToSubjects(const QString &item) const;

    QStringList selectFromGroups() const;
    QStringList selectFromSubjects() const;
    int selectIdFromUsers(const QString& login) const;
    QByteArray selectPasswordFromUsers(const QString &login) const;
    QByteArray selectSaltFromUsers(const QString &login) const;

    bool deleteFromGroups(const QString &item) const;
    bool deleteFromSubjects(const QString &item) const;

    QSqlDatabase *database();

private:
    QSqlDatabase m_db;

    bool createDatabaseFile(const QString &path) const;
    bool createTables() const;

    bool insertToTable(const QString &item,
                       const QString &table,
                       const QString &column) const;

    QStringList selectFromTable(const QString &table,
                                const QString &column) const;

    //not working
    QStringList selectFromTable(const QString &table,
                                const QString &column,
                                const QString &condition) const;

    QByteArray selectFromUsersByLogin(const QString &login,
                                      const QString &column) const;

    bool deleteFromTable(const QString &item,
                         const QString &table,
                         const QString &column) const;

    bool isItemInTable(const QString &item,
                       const QString &table,
                       const QString &column) const;

    template<typename T>
    bool insertToTable(const QList<T> items,
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
};

#endif // DATABASEMANAGER_H
