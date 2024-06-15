#ifndef REPORTSLISTWIDGET_H
#define REPORTSLISTWIDGET_H

#include <QListWidget>

class ReportListItemWidget;

class ReportsListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ReportsListWidget(QWidget *parent = nullptr);

    void addEmptyItem();
    void deleteCurrentItem();
    bool isItemInList(const QDate &date) const;

private:
    QListWidgetItem *emptyItem = nullptr;

    QListWidgetItem *createItem();
    QListWidgetItem *createItem(const QDate &date);
    void setupItemsFromDatabase();
    ReportListItemWidget *reportListItemWidget(QListWidgetItem *item) const;

signals:
    void reportSelected(const QDate &date, QListWidgetItem *report);
    void reportsDeleted();

public slots:
    void onReportSaved(const QDate &date);

private slots:
    void onItemClicked(QListWidgetItem *item);
};

#endif // REPORTSLISTWIDGET_H
