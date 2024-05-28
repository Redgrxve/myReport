#include "studentslistedit.h"

StudentsListEdit::StudentsListEdit(const QString &group, QWidget *parent)
    : ListEditWidget(parent)
    , m_group(group)
{

}

bool StudentsListEdit::addToDatabase(const QString &item)
{
    return true;
}

bool StudentsListEdit::deleteFromDatabase(const QString &item)
{
    return true;
}
