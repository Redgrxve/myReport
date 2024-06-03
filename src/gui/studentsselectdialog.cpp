#include "studentsselectdialog.h"
#include "ui_studentsselectdialog.h"
#include "databasemanager.h"

StudentsSelectDialog::StudentsSelectDialog(int groupId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StudentsSelectDialog)
    , m_groupId(groupId)
{
    ui->setupUi(this);

    ui->listWidget->addItems(
        DatabaseManager::instance()->selectNamesFromStudents(m_groupId));
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &StudentsSelectDialog::onAccepted);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked,
            this, &StudentsSelectDialog::onItemDoubleClicked);
}

StudentsSelectDialog::~StudentsSelectDialog()
{
    delete ui;
}

void StudentsSelectDialog::onAccepted()
{
    emit studentSelected(ui->listWidget->currentItem()->text());
}

void StudentsSelectDialog::onItemDoubleClicked(QListWidgetItem *item)
{
    emit studentSelected(item->text());
    accept();
}

