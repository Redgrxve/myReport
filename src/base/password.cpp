#include "password.h"
#include "openssl/evp.h"

#include <QRandomGenerator>
#include <QDebug>

Password::Password()
{
    m_salt = generateSalt();
}

Password::Password(const QString &str)
{
    m_hash = generateHash(str);
}

Password &Password::operator=(const QString &str)
{
    m_hash = generateHash(str);
    return *this;
}

bool Password::operator==(const Password &other)
{
    return other.m_hash == m_hash;
}

bool Password::operator!=(const Password &other)
{
    qDebug() << other.m_hash;
    qDebug() << m_hash << "\n";
    return other.m_hash != m_hash;
}

bool Password::compareWith(const QString &password)
{
    return m_hash == password;
}

QByteArray Password::generateHash(const QString &str)
{
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        qFatal("Unable to create EVP_MD_CTX");
    }

    // Указание алгоритма хэширования (SHA-256)
    const EVP_MD* md = EVP_sha256();

    // Инициализация контекста
    if (EVP_DigestInit_ex(context, md, nullptr) != 1) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestInit_ex failed");
    }

    // Обновление контекста данными
    QByteArray inputBytes = str.toUtf8();
    if (EVP_DigestUpdate(context, inputBytes.constData(), inputBytes.size()) != 1) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestUpdate failed");
    }

    // Завершение хэширования и получение результата
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) {
        EVP_MD_CTX_free(context);
        qFatal("EVP_DigestFinal_ex failed");
    }

    // Освобождение контекста
    EVP_MD_CTX_free(context);

    // Преобразование результата в QByteArray и возврат
    return QByteArray(reinterpret_cast<char*>(hash), lengthOfHash);
}

bool Password::compare(const QString &input, const QString &storedHash)
{
    QByteArray hashedInput = generateHash(input);
    return hashedInput == storedHash;
}

QByteArray Password::generateSalt(int length)
{
    QByteArray salt;
    salt.resize(length);
    for (int i = 0; i < length; ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::global()->bounded(256));
    }
    return salt;
}

QString Password::toString() const
{
    return QString::fromUtf8(m_hash);
}

bool Password::isEmpty() const
{
    return toString().isEmpty();
}
