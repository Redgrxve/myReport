#ifndef NAMEVALIDATOR_H
#define NAMEVALIDATOR_H

#include <QValidator>

class NameValidator : public QValidator
{
public:
    explicit NameValidator(QObject *parent = nullptr);

    State validate(QString &input, int &pos) const override;
    void fixup(QString &input) const override;
};

#endif // NAMEVALIDATOR_H
