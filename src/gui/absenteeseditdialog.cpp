#include "absenteeseditdialog.h"
#include "ui_absenteeseditdialog.h"
#include "studentsselectdialog.h"

AbsenteesEditDialog::AbsenteesEditDialog(int groupId,
                                         const QStringList &names,
                                         QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AbsenteesEditDialog)
    , m_groupId(groupId)
{
    ui->setupUi(this);

    ui->listWidget->addItems(names);

    connect(ui->addButton, &QPushButton::clicked,
            this, &AbsenteesEditDialog::onAddClicked);
    connect(ui->removeButton, &QPushButton::clicked,
            this, &AbsenteesEditDialog::onRemoveClicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &AbsenteesEditDialog::onSaveClicked);
}

AbsenteesEditDialog::~AbsenteesEditDialog()
{
    delete ui;
}

void AbsenteesEditDialog::onAddClicked()
{
    StudentsSelectDialog studentsDialog(m_groupId, this);
    connect(&studentsDialog, &StudentsSelectDialog::studentSelected,
            this, &AbsenteesEditDialog::onStudentSelected);
    studentsDialog.exec();
}

void AbsenteesEditDialog::onRemoveClicked()
{
    auto selectedItem = ui->listWidget->currentItem();
    if (!selectedItem)
        return;

    delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));
}

void AbsenteesEditDialog::onStudentSelected(const QString &name)
{
    if (!ui->listWidget->findItems(name, Qt::MatchExactly).isEmpty()) {
        return;
    }
    ui->listWidget->addItem(name);
}

void AbsenteesEditDialog::onSaveClicked()
{
    QStringList names;
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        auto item = ui->listWidget->item(i);
        names.append(item->text());
    }
    emit absenteesSaved(names);
}
