#include "reportdetailswidget.h"
#include "ui_reportdetailswidget.h"
#include "calendardialog.h"

ReportDetailsWidget::ReportDetailsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportDetailsWidget)
{
    ui->setupUi(this);

    connect(ui->celendarButton, SIGNAL(clicked()), this, SLOT(onCalendarButtonClicked()));
}

ReportDetailsWidget::~ReportDetailsWidget()
{
    delete ui;
}

void ReportDetailsWidget::onCalendarButtonClicked()
{
    CalendarDialog calendarDialog;
    connect(&calendarDialog, SIGNAL(dateSelected(QDate)), this, SLOT(onDateSelected(QDate)));
    calendarDialog.exec();
}

void ReportDetailsWidget::onDateSelected(const QDate &date)
{
    ui->dateLabel->setText(date.toString("dd.MM.yyyy"));

    QLocale locale = QLocale(QLocale::Russian);
    QString localeDate = locale.toString(date, "dddd");
    ui->dayLabel->setText(localeDate);
}
