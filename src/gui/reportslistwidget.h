#ifndef REPORTSLISTWIDGET_H
#define REPORTSLISTWIDGET_H

#include <QListWidget>

class ReportsListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit ReportsListWidget(QWidget *parent = nullptr);

    void addEmptyItem();
    bool isItemInList(const QDate &date) const;

private:
    QListWidgetItem *createItem();
    QListWidgetItem *createItem(const QDate &date);
    void setupItemsFromDatabase();

signals:
    void reportSelected(const QDate &date);

public slots:
    void onReportSaved(const QDate &date,
                       const QHash<int, QStringList> &absentees);

private slots:
    void onItemClicked(QListWidgetItem *item);
};

#endif // REPORTSLISTWIDGET_H
