#include "reportdetailswidget.h"
#include "ui_reportdetailswidget.h"
#include "calendardialog.h"
#include "comboboxdelegate.h"
#include "lineeditwithbuttondelegate.h"

ReportDetailsWidget::ReportDetailsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportDetailsWidget)
{
    ui->setupUi(this);

    setupDelegates();
    connect(ui->celendarButton, SIGNAL(clicked()), this, SLOT(onCalendarButtonClicked()));
    connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(insertRow()));
    connect(this, SIGNAL(rowInserted(int)), this, SLOT(onRowInserted(int)));
}

ReportDetailsWidget::~ReportDetailsWidget()
{
    delete ui;
}

void ReportDetailsWidget::setupDelegates()
{
    ComboBoxDelegate *comboBoxDelegate = new ComboBoxDelegate(ui->tableWidget);
    ui->tableWidget->setItemDelegateForColumn(0, comboBoxDelegate);

    LineEditWithButtonDelegate *lineEditButtonDelegate = new LineEditWithButtonDelegate(ui->tableWidget);
    ui->tableWidget->setItemDelegateForColumn(1, lineEditButtonDelegate);
}

void ReportDetailsWidget::onCalendarButtonClicked()
{
    CalendarDialog calendarDialog(this);
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

void ReportDetailsWidget::insertRow()
{
    int newRowIndex = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRowIndex);
    emit rowInserted(newRowIndex);
}

void ReportDetailsWidget::onRowInserted(int newRowIndex)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(newRowIndex, 0, item);
}
