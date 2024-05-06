#include "starterdialog.h"
#include "ui_starterdialog.h"

StarterDialog::StarterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StarterDialog)
{
    ui->setupUi(this);

    ui->newTeacherGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxToggled(bool)));
}

StarterDialog::~StarterDialog()
{
    delete ui;
}

void StarterDialog::onCheckBoxToggled(bool checked)
{
    ui->newTeacherGroupBox->setVisible(checked);
}
