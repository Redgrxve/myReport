#include "appconfig.h"
#include "databasemanager.h"

Q_GLOBAL_STATIC(AppConfig, appConfigInstance)

AppConfig::AppConfig() {}
AppConfig::~AppConfig() {}

AppConfig *AppConfig::instance()
{
    return appConfigInstance;
}

void AppConfig::setUser(const QString &user)
{
    m_user = user;
    m_userId = DatabaseManager::instance()->selectIdFromUsers(user);
    DatabaseManager::instance()->setUserId(m_userId);
    qDebug() << "login: " << m_user << ", id: " << m_userId;
}

void AppConfig::setUser(const QString &user, int id)
{
    m_user = user;
    m_userId = id;
    DatabaseManager::instance()->setUserId(m_userId);
    qDebug() << "login: " << m_user << ", id: " << m_userId;
}

QString AppConfig::user() const
{
    return m_user;
}

int AppConfig::userId() const
{
    return m_userId;
}
