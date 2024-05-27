#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>

class AppConfig
{
public:
    AppConfig();
    ~AppConfig();
    AppConfig(const AppConfig& other) = delete;
    AppConfig& operator=(const AppConfig& other) = delete;

    static AppConfig *instance();

    void setCurrentUser(const QString& login, int id);
    QString currentUser() const;

private:
    QString m_user;
    int m_userId;
};

#endif // APPCONFIG_H
