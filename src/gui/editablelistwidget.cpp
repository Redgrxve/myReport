#include "editablelistwidget.h"
#include "ui_editablelistwidget.h"

#include <QInputDialog>
#include <QMessageBox>

EditableListWidget::EditableListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EditableListWidget)
{
    ui->setupUi(this);

    setFixedWidth(sizeHint().width());

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
    QString groupName = QInputDialog::getText(this, tr("Добавление нового элемента"),
                                              tr("Введите наименование"),
                                              QLineEdit::Normal, "", &okPressed);
    if (!okPressed)
        return;

    if (groupName.isEmpty()) {
        QMessageBox::warning(this, "Внимание",
                             "Поле должно быть заполнено.");
        return;
    }

    if (!addToDatabase(groupName)) {
        QMessageBox::critical(this, "Ошибка",
                              "Ошибка при добавлении элемента в базу данных."
                              "\nВозможно, элемент уже добавлена в список."
                              "\nПопробуйте еще раз.");
        return;
    }

    listWidget()->addItem(groupName);
    listWidget()->sortItems();
}

void EditableListWidget::removeSelectedItem()
{
    auto selectedItem = listWidget()->currentItem();
    if (!selectedItem)
        return;

    if (!deleteFromDatabase(selectedItem->text())) {
        QMessageBox::critical(this, "Ошибка",
                              "Ошибка при удалении элемента из базы данных."
                              "\nПопробуйте еще раз.");
        return;
    }

    delete listWidget()->takeItem(listWidget()->row(selectedItem));
}

QListWidget *EditableListWidget::listWidget() const
{
    return ui->listWidget;
}

void EditableListWidget::onAddButtonClicked()
{
    addNewItem();
}

void EditableListWidget::onDeleteButtonClicked()
{
    removeSelectedItem();
}
