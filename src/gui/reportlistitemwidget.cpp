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
