#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>


//УДАЛИТЬ ЛИШНЕЕЕЕЕЕЕЕЕЕЕЕЕ


class Password
{
public:
    Password();
    Password(const QString &str);

    Password &operator=(const QString &str);
    bool operator==(const Password &other);
    bool operator!=(const Password &other);

    static QByteArray generateHash(const QString &str);
    static bool compare(const QString &input,
                        const QString &storedHash);

    QString toString() const;
    bool isEmpty() const;

private:
    QByteArray generateSalt(int length = 16);
    bool compareWith(const QString &password);
    QByteArray m_hash;
    QByteArray m_salt;
};

#endif // PASSWORD_H
