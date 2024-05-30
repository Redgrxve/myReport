#include "calendardialog.h"
#include "ui_calendardialog.h"

CalendarDialog::CalendarDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CalendarDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(onAccepted()));
}

CalendarDialog::~CalendarDialog()
{
    delete ui;
}

void CalendarDialog::onAccepted()
{
    emit dateSelected(ui->calendarWidget->selectedDate());
}
