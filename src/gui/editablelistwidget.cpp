#include "editablelistwidget.h"
#include "ui_editablelistwidget.h"

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

void EditableListWidget::onAddButtonClicked()
{
    addNewItem();
}

void EditableListWidget::onDeleteButtonClicked()
{
    removeSelectedItem();
}
