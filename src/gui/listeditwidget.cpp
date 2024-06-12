#include "listeditwidget.h"
#include "ui_listeditwidget.h"

#include <QInputDialog>
#include <QMessageBox>

ListEditWidget::ListEditWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ListEditWidget)
{
    ui->setupUi(this);

    setFixedWidth(sizeHint().width());

    connect(ui->addButton, &QPushButton::clicked,
            this, &ListEditWidget::onAddButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked,
            this, &ListEditWidget::onDeleteButtonClicked);
}

ListEditWidget::~ListEditWidget()
{
    delete ui;
}

bool ListEditWidget::isItemInList(const QString &text) const
{
    QList<QListWidgetItem*> items = ui->listWidget->findItems(text, Qt::MatchExactly);
    return !items.isEmpty();
}

void ListEditWidget::addNewItem()
{
    bool okPressed;
    QString itemName = QInputDialog::getText(this, tr("Добавление нового элемента"),
                                              tr("Введите наименование"),
                                              QLineEdit::Normal, "", &okPressed);
    if (!okPressed)
        return;

    if (itemName.isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                             tr("Поле должно быть заполнено."));
        return;
    }

    if (!addToDatabase(itemName)) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Ошибка при добавлении элемента."
                              "\nВозможно, элемент уже добавлена в список."
                                 "\nПопробуйте еще раз."));
        return;
    }

    listWidget()->addItem(itemName);
}

void ListEditWidget::removeSelectedItem()
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
                                 "\nПопробуйте еще раз."));
        return;
    }

    delete listWidget()->takeItem(listWidget()->row(selectedItem));
}

QListWidget *ListEditWidget::listWidget() const
{
    return ui->listWidget;
}

void ListEditWidget::onAddButtonClicked()
{
    addNewItem();
}

void ListEditWidget::onDeleteButtonClicked()
{
    removeSelectedItem();
}
