#include "absenteeseditdialog.h"
#include "ui_absenteeseditdialog.h"
#include "studentsselectdialog.h"

AbsenteesEditDialog::AbsenteesEditDialog(int groupId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AbsenteesEditDialog)
    , m_groupId(groupId)
{
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked,
            this, &AbsenteesEditDialog::onAddButtonClicked);
}

AbsenteesEditDialog::~AbsenteesEditDialog()
{
    delete ui;
}

void AbsenteesEditDialog::onAddButtonClicked()
{
    StudentsSelectDialog studentsDialog(m_groupId, this);
    studentsDialog.exec();
}
