#include "groupslistwidget.h"
#include "databasemanager.h"

GroupsListWidget::GroupsListWidget(QWidget* parent)
    : EditableListWidget(parent)
{
    setWindowTitle("Список групп");
    listWidget()->addItems(DatabaseManager::instance()->selectFromGroups());
}

bool GroupsListWidget::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToGroups(item);
}

bool GroupsListWidget::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromGroups(item);
}
