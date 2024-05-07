#include "starterdialog.h"
#include "mainwindow.h"
#include "nospacevalidator.h"
#include "ui_starterdialog.h"

#include <QMessageBox>

StarterDialog::StarterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StarterDialog)
{
    ui->setupUi(this);

    if (ui->comboBox->count() == 0)
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    NoSpaceValidator *validator = new NoSpaceValidator(this);
    ui->lastNameLineEdit->setValidator(validator);
    ui->firstNameLineEdit->setValidator(validator);
    ui->patronymicLineEdit->setValidator(validator);

    ui->newTeacherGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxToggled(bool)));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddClicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxChanged()));
}

StarterDialog::~StarterDialog()
{
    delete ui;
}

void StarterDialog::onCheckBoxToggled(bool checked)
{
    ui->newTeacherGroupBox->setVisible(checked);
}

void StarterDialog::onAddClicked()
{
    if (ui->lastNameLineEdit->text().isEmpty()
        || ui->firstNameLineEdit->text().isEmpty()
        || ui->patronymicLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                                   tr("Необходимо заполнить все поля"));
        return;
    }

    QString newTeacherName =
        ui->lastNameLineEdit->text() + " "
        + ui->firstNameLineEdit->text() + " "
        + ui->patronymicLineEdit->text();

    ui->comboBox->addItem(newTeacherName);

    ui->lastNameLineEdit->clear();
    ui->firstNameLineEdit->clear();
    ui->patronymicLineEdit->clear();
}

void StarterDialog::onComboBoxChanged()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void StarterDialog::createMainWindow()
{
    MainWindow* mainWindow = new MainWindow;
    mainWindow->show();
}
