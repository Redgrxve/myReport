#ifndef REPORTDETAILSWIDGET_H
#define REPORTDETAILSWIDGET_H

#include <QDate>
#include <QWidget>

namespace Ui {
class ReportDetailsWidget;
}

class ReportDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportDetailsWidget(QWidget *parent = nullptr);
    ~ReportDetailsWidget();

private:
    Ui::ReportDetailsWidget *ui;
    QDate m_date;

    void setupDelegates();
    void insertRow();
    void removeLastRow();
    QStringList availableGroups(const QString &currentGroup) const;
    //СДЕЛАТЬ ПОТОМ ЧТОБЫ КОМБОБОКСЫ ОБНОВЛЯЛИСЬ ПРИ УДАЛЕНИИ ЭЛЕМЕНТОВ ИЗ СПИСКА
    //void updateComboBoxes();

signals:
    void rowInserted(int newRowIndex);
    void saveClicked(const QDate &date,
                     const QHash<int, QStringList> &absentees);

public slots:
    void setupFromDatabase(const QDate &date);

private slots:
    void onCalendarButtonClicked();
    void onDateSelected(const QDate &date);
    void onRowInserted(int newRowIndex);
    void onCellEdit(int row, int column);
    void onSaveClicked();
};

#endif // REPORTDETAILSWIDGET_H
