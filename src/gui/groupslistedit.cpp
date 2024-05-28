#include "groupslistedit.h"
#include "databasemanager.h"
#include "studentslistedit.h"

GroupsListEdit::GroupsListEdit(QWidget* parent)
    : ListEditWidget(parent)
{
    setWindowTitle(tr("Список групп"));
    listWidget()->addItems(DatabaseManager::instance()->selectNamesFromGroups());
    connect(listWidget(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
}

bool GroupsListEdit::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToGroups(item);
}

bool GroupsListEdit::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromGroups(item);
}

void GroupsListEdit::onItemDoubleClicked(QListWidgetItem *item)
{
    QString itemText = item->text();
    StudentsListEdit* studentsListEdit = new StudentsListEdit(itemText);
    studentsListEdit->setWindowTitle("Состав группы " + itemText);
    studentsListEdit->show();
}
