#include "editablelistwidget.h"
#include "ui_editablelistwidget.h"
#include "databasemanager.h"

#include <QInputDialog>
#include <QMessageBox>

EditableListWidget::EditableListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditableListWidget)
{
    ui->setupUi(this);

    setFixedWidth(sizeHint().width());
    ui->listWidget->addItems(DatabaseManager::instance()->selectFromGroups());

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));
}

EditableListWidget::~EditableListWidget()
{
    delete ui;
}

bool EditableListWidget::isItemInList(const QString &text) const
{
    QList<QListWidgetItem*> items = ui->listWidget->findItems(text, Qt::MatchExactly);
    return !items.isEmpty();
}

void EditableListWidget::addNewItem()
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

void EditableListWidget::removeSelectedItem()
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

void EditableListWidget::onAddButtonClicked()
{
    addNewItem();
}

void EditableListWidget::onDeleteButtonClicked()
{
    removeSelectedItem();
}
