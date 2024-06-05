#include "reportslistwidget.h"
#include "reportlistitemwidget.h"

ReportsListWidget::ReportsListWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &ReportsListWidget::itemClicked,
            this, &ReportsListWidget::onItemClicked);
}

void ReportsListWidget::addEmptyItem()
{
    addItem(createItem());
}

QListWidgetItem *ReportsListWidget::createItem()
{
    QListWidgetItem *item = new QListWidgetItem(this);
    ReportListItemWidget *itemWidget = new ReportListItemWidget(this);
    item->setSizeHint(QSize(0, 40));
    setItemWidget(item, itemWidget);
    return item;
}

QListWidgetItem *ReportsListWidget::createItem(const QDate &date)
{
    QListWidgetItem *item = new QListWidgetItem(this);
    ReportListItemWidget *itemWidget = new ReportListItemWidget(this);
    item->setSizeHint(QSize(0, 40));
    itemWidget->setDate(date);
    setItemWidget(item, itemWidget);
    return item;
}

void ReportsListWidget::onReportSaved(const QDate &date,
                                      const QHash<int, QStringList> &absentees)
{
    addItem(createItem(date));
}

void ReportsListWidget::onItemClicked(QListWidgetItem *item)
{
    auto reportItemWidget = static_cast<ReportListItemWidget*>(itemWidget(item));
    emit reportSelected(reportItemWidget->date());
}
