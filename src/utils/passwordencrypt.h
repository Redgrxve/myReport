#ifndef PASSWORDENCRYPT_H
#define PASSWORDENCRYPT_H

#include "openssl/evp.h"
#include "openssl/rand.h"

#include <QDebug>
#include <QString>

QT_BEGIN_NAMESPACE
namespace PasswordEncrypt {

QByteArray generateHash(const QString &password,
                        const QByteArray &salt)
{
    QByteArray saltedPassword = password.toUtf8() + salt;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        qFatal("Unable to create EVP_MD_CTX");
    }

    // Указание алгоритма хэширования (SHA-256)
    const EVP_MD* md = EVP_sha256();

    // Инициализация контекста
    if (!EVP_DigestInit_ex(context, md, nullptr)) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestInit_ex failed");
    }

    // Обновление контекста данными
    if (!EVP_DigestUpdate(context,
                          saltedPassword.constData(),
                          saltedPassword.size())) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestUpdate failed");
    }

    // Завершение хэширования и получение результата
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (!EVP_DigestFinal_ex(context, hash, &lengthOfHash)) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestFinal_ex failed");
    }

    // Освобождение контекста
    EVP_MD_CTX_free(context);

    // Преобразование результата в QByteArray и возврат
    return QByteArray(reinterpret_cast<char*>(hash), lengthOfHash);
}

QByteArray generateSalt()
{
    const int SALT_LENGTH = 16;
    QByteArray salt(SALT_LENGTH, 0);
    if (!RAND_bytes(reinterpret_cast<unsigned char*>(salt.data()),
                    SALT_LENGTH)) {
        qFatal("RAND_bytes failed");
    }
    return salt;
}

bool compare(const QString &input,
             const QByteArray &hashedPassword,
             const QByteArray &salt)
{
    QByteArray hashedInput = generateHash(input, salt);
    return hashedInput == hashedPassword;
}

}
QT_END_NAMESPACE

#endif // PASSWORDENCRYPT_H
