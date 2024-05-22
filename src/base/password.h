#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>

class Password
{
public:
    Password();
    Password(const QString &str);

private:
    QString encrypt();
    QString decrypt();
    QString generateSalt();
};

#endif // PASSWORD_H
