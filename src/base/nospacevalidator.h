#ifndef NOSPACEVALIDATOR_H
#define NOSPACEVALIDATOR_H

#include <QValidator>

class NoSpaceValidator : public QValidator
{
public:
    explicit NoSpaceValidator(QObject *parent = nullptr);

    State validate(QString &input, int &pos) const override;
};

#endif // NOSPACEVALIDATOR_H
