#include "reportslistwidget.h"
#include "databasemanager.h"
#include "reportlistitemwidget.h"

#include <QMessageBox>

ReportsListWidget::ReportsListWidget(QWidget *parent)
    : QListWidget(parent)
{
    connect(this, &ReportsListWidget::itemClicked,
            this, &ReportsListWidget::onItemClicked);

    setupItemsFromDatabase();
}

void ReportsListWidget::addEmptyItem()
{
    if (emptyItem)
        return;

    QListWidgetItem *item = createItem();
    addItem(item);
    setCurrentItem(item);
    emit itemClicked(item);
}

void ReportsListWidget::deleteCurrentItem()
{
    if (!currentItem())
        return;

    QDate date = reportListItemWidget(currentItem())->date();
    QString questionText = date.isValid() ? tr("Вы точно хотите удалить рапортичку на ") + date.toString("dd.MM.yyyy") + "?"
                                          : tr("Вы точно хотите удалить незаполненную рапортичку?");
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                  tr("Внимание"),
                                  questionText);
    if (reply == QMessageBox::StandardButton::No)
        return;

    auto dbManager = DatabaseManager::instance();
    auto reportItemWidget = reportListItemWidget(currentItem());
    dbManager->deleteFromAbsentees(reportItemWidget->date());
    if (currentItem() == emptyItem)
        emptyItem = nullptr;

    delete takeItem(currentRow());
    emit reportDeleted(date);

    if (currentItem())
        emit itemClicked(currentItem());

    if (count() == 0)
        emit allReportsDeleted();
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

QListWidgetItem *ReportsListWidget::itemByDate(const QDate &date)
{
    for (int row = 0; row < count(); ++row) {
        auto reportItem = item(row);
        auto reportItemWidget = reportListItemWidget(reportItem);
        if (date == reportItemWidget->date())
            return reportItem;
    }

    return nullptr;
}

void ReportsListWidget::onReportSaved(const QDate &date)
{
    clear();
    setupItemsFromDatabase();
    emptyItem = nullptr;

    auto item = itemByDate(date);
    if (item)
        setCurrentItem(item);
}

void ReportsListWidget::onItemClicked(QListWidgetItem *item)
{
    auto reportItemWidget = reportListItemWidget(item);
    emit reportSelected(reportItemWidget->date());
}
