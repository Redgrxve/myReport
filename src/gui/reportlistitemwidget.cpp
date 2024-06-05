#include "reportlistitemwidget.h"
#include "ui_reportlistitemwidget.h"

ReportListItemWidget::ReportListItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReportListItemWidget)
{
    ui->setupUi(this);
}

ReportListItemWidget::~ReportListItemWidget()
{
    delete ui;
}

void ReportListItemWidget::setDate(const QDate &date)
{
    m_date = date;
    ui->dateLabel->setText(date.toString("dd.MM.yyyy"));

    QLocale locale = QLocale(QLocale::Russian);
    QString localeDate = locale.toString(date, "dddd");
    ui->dayLabel->setText(localeDate);
}

QDate ReportListItemWidget::date() const
{
    return m_date;
}
