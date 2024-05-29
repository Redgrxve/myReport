#include "studentslistedit.h"
#include "databasemanager.h"

StudentsListEdit::StudentsListEdit(int groupId, QWidget *parent)
    : ListEditWidget(parent)
    , m_groupId(groupId)
{
    listWidget()->addItems(DatabaseManager::instance()->selectNamesFromStudents(m_groupId));
}

bool StudentsListEdit::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToStudents(item, m_groupId);
}

bool StudentsListEdit::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromStudents(item, m_groupId);
}
