#include "reportslistwidget.h"
#include "databasemanager.h"
#include "reportlistitemwidget.h"

ReportsListWidget::ReportsListWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &ReportsListWidget::itemClicked,
            this, &ReportsListWidget::onItemClicked);

    setupItemsFromDatabase();
}

void ReportsListWidget::addEmptyItem()
{
    if (!emptyItem)
        addItem(createItem());
}

QListWidgetItem *ReportsListWidget::createItem()
{
    emptyItem = new QListWidgetItem(this);
    ReportListItemWidget *itemWidget = new ReportListItemWidget(this);
    emptyItem->setSizeHint(QSize(0, 40));
    setItemWidget(emptyItem, itemWidget);
    return emptyItem;
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

void ReportsListWidget::setupItemsFromDatabase()
{
    QList<QDate> dates = DatabaseManager::instance()->selectDatesFromAbsentees();
    for (const QDate &date : dates) {
        addItem(createItem(date));
    }
}

ReportListItemWidget *ReportsListWidget::reportListItemWidget(QListWidgetItem *item) const
{
    return static_cast<ReportListItemWidget*>(itemWidget(item));
}

bool ReportsListWidget::isItemInList(const QDate &date) const
{
    for (int row = 0; row < count(); ++row) {
        auto reportItemWidget = reportListItemWidget(item(row));
        if (date == reportItemWidget->date())
            return true;
    }
    return false;
}

void ReportsListWidget::onReportSaved(const QDate &date)
{
    clear();
    setupItemsFromDatabase();
    emptyItem = nullptr;
}

void ReportsListWidget::onItemClicked(QListWidgetItem *item)
{
    auto reportItemWidget = reportListItemWidget(item);
    emit reportSelected(reportItemWidget->date());
}
