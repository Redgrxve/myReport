#include "groupslistedit.h"
#include "databasemanager.h"
#include "studentslistedit.h"
#include "windowmanager.h"

#include <QMessageBox>

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

void GroupsListEdit::removeSelectedItem()
{
    auto selectedItem = listWidget()->currentItem();
    if (!selectedItem)
        return;

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Удаление выбранного элемента"),
                                  tr("Вы действительно хотите удалить выбранный элемент?"));
    if (reply == QMessageBox::StandardButton::No)
        return;

    if (!deleteFromDatabase(selectedItem->text())) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Ошибка при удалении элемента из базы данных."
                                 "\nГруппу нельзя удалить, если она присутствует в рапортичках."));
        return;
    }

    delete listWidget()->takeItem(listWidget()->row(selectedItem));
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
    studentsListEdit->setWindowTitle("Состав группы " + item->text());
    studentsListEdit->show();
    m_windowManager->add(studentsListEdit);
}
