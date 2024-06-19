#ifndef PASSWORDENCRYPT_H
#define PASSWORDENCRYPT_H

#include <QString>

QT_BEGIN_NAMESPACE
namespace PasswordEncrypt {

QByteArray generateHash(const QString &password, const QByteArray &salt);
QByteArray generateSalt();
bool compare(const QString &input,
             const QByteArray &hashedPassword,
             const QByteArray &salt);

}
QT_END_NAMESPACE

#endif // PASSWORDENCRYPT_H
