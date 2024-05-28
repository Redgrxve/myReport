#include "groupslistedit.h"
#include "databasemanager.h"

GroupsListEdit::GroupsListEdit(QWidget* parent)
    : ListEditWidget(parent)
{
    setWindowTitle(tr("Список групп"));
    listWidget()->addItems(DatabaseManager::instance()->selectNamesFromGroups());
}

bool GroupsListEdit::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToGroups(item);
}

bool GroupsListEdit::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromGroups(item);
}
