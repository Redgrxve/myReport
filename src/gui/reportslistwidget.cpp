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

void ReportsListWidget::setupItemsFromDatabase()
{
    QList<QDate> dates = DatabaseManager::instance()->selectDatesFromAbsentees();
    for (const QDate &date : dates) {
        addItem(createItem(date));
    }
}

bool ReportsListWidget::isItemInList(const QDate &date) const
{
    for (int row = 0; row < count(); ++row) {
        auto reportItemWidget = static_cast<ReportListItemWidget*>(itemWidget(item(row)));
        if (date == reportItemWidget->date())
            return true;
    }
    return false;
}

void ReportsListWidget::onReportSaved(const QDate &date,
                                      const QHash<int, QStringList> &absentees)
{
    if (!isItemInList(date))
        addItem(createItem(date));
}

void ReportsListWidget::onItemClicked(QListWidgetItem *item)
{
    auto reportItemWidget = static_cast<ReportListItemWidget*>(itemWidget(item));
    emit reportSelected(reportItemWidget->date());
}
