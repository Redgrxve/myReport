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
}

StudentsSelectDialog::~StudentsSelectDialog()
{
    delete ui;
}
