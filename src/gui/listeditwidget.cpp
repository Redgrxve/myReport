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
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));
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
    QString groupName = QInputDialog::getText(this, tr("Добавление нового элемента"),
                                              tr("Введите наименование"),
                                              QLineEdit::Normal, "", &okPressed);
    if (!okPressed)
        return;

    if (groupName.isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                             tr("Поле должно быть заполнено."));
        return;
    }

    if (!addToDatabase(groupName)) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Ошибка при добавлении элемента."
                              "\nВозможно, элемент уже добавлена в список."
                                 "\nПопробуйте еще раз."));
        return;
    }

    listWidget()->addItem(groupName);
}

void ListEditWidget::removeSelectedItem()
{
    auto selectedItem = listWidget()->currentItem();
    if (!selectedItem)
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
