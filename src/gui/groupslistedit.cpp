#include "groupslistedit.h"
#include "databasemanager.h"
#include "studentslistedit.h"
#include "windowmanager.h"

GroupsListEdit::GroupsListEdit(WindowManager* windowManager,
                               QWidget* parent)
    : ListEditWidget(parent)
    , m_windowManager(windowManager)
{
    setWindowTitle(tr("Список групп"));
    listWidget()->addItems(DatabaseManager::instance()->selectNamesFromGroups());
    connect(listWidget(), SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(onItemDoubleClicked(QListWidgetItem*)));
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
    int groupId = DatabaseManager::instance()->selectIdFromGroups(item->text());
    StudentsListEdit* studentsListEdit = new StudentsListEdit(groupId);
    studentsListEdit->setWindowTitle(item->text());
    studentsListEdit->show();
    m_windowManager->add(studentsListEdit);
}
