#include "nospacevalidator.h"

NoSpaceValidator::NoSpaceValidator(QObject *parent)
    : QValidator{parent}
{}

QValidator::State NoSpaceValidator::validate(QString &input, int &pos) const
{
    if (input.contains(" "))
        return QValidator::Invalid;

    return QValidator::Acceptable;
}
