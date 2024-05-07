#include "namevalidator.h"

NameValidator::NameValidator(QObject *parent)
    : QValidator{parent}
{}

QValidator::State NameValidator::validate(QString &input, int &pos) const
{
    if (input[0].isLower())
        return Invalid;

    for (int i = 1; i < input.size(); ++i) {
        if (input[i].isUpper())
            return Invalid;
    }

    return Acceptable;
}

void NameValidator::fixup(QString &input) const
{
    if (input.isEmpty()) return;

    input[0] = input[0].toUpper();
    for (int i = 1; i < input.size(); ++i) {
        input[i] = input[i].toLower();
    }
}
