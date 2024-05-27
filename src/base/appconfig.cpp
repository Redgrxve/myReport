#include "appconfig.h"

Q_GLOBAL_STATIC(AppConfig, appConfigInstance)

AppConfig::AppConfig() {}
AppConfig::~AppConfig() {}

AppConfig *AppConfig::instance()
{
    return appConfigInstance;
}

void AppConfig::setCurrentUser(const QString &user, int id)
{
    m_user = user;
    m_userId = id;
}

QString AppConfig::currentUser() const
{
    return m_user;
}
