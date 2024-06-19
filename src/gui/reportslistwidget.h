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
    QListWidgetItem *itemByDate(const QDate &date);
    void setupItemsFromDatabase();
    ReportListItemWidget *reportListItemWidget(QListWidgetItem *item) const;

signals:
    void reportSelected(const QDate &date);
    void reportDeleted(const QDate &date);
    void allReportsDeleted();

public slots:
    void onReportSaved(const QDate &date);

private slots:
    void onItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // REPORTSLISTWIDGET_H
