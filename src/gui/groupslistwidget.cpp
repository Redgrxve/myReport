#include "groupslistwidget.h"
#include "ui_editablelistwidget.h"
#include "databasemanager.h"

#include <QInputDialog>
#include <QMessageBox>

GroupsListWidget::GroupsListWidget(QWidget* parent)
    : EditableListWidget(parent)
{
    ui->listWidget->addItems(DatabaseManager::instance()->selectFromGroups());
}

GroupsListWidget::~GroupsListWidget() {}

void GroupsListWidget::addNewItem()
{
    bool okPressed;
    QString groupName = QInputDialog::getText(this, tr("Добавление новой группы"),
                                              tr("Введите название новой группы"),
                                              QLineEdit::Normal, "", &okPressed);
    if (!okPressed)
        return;

    if (groupName.isEmpty()) {
        QMessageBox::warning(this, "Внимание",
                             "Название группы должно быть заполнено.");
        return;
    }

    if (!DatabaseManager::instance()->insertToGroups(groupName)) {
        QMessageBox::critical(this, "Ошибка",
                              "Ошибка при добавлении группы."
                              "\nВозможно, группа уже добавлена в список."
                              "\nПопробуйте еще раз.");
        return;
    }

    ui->listWidget->addItem(groupName);
    ui->listWidget->sortItems();
}

void GroupsListWidget::removeSelectedItem()
{
    auto selectedItem = ui->listWidget->currentItem();
    if (!selectedItem)
        return;

    if (!DatabaseManager::instance()->deleteFromGroups(selectedItem->text())) {
        QMessageBox::critical(this, "Ошибка",
                              "Ошибка при удалении группы."
                              "\nПопробуйте еще раз.");
        return;
    }

    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));
}
