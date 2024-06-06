#ifndef REPORTDETAILSWIDGET_H
#define REPORTDETAILSWIDGET_H

#include <QDate>
#include <QWidget>

class AbsenteesItemDelegate;
class GroupsComboBoxDelegate;

namespace Ui {
class ReportDetailsWidget;
}

class ReportDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportDetailsWidget(QWidget *parent = nullptr);
    ~ReportDetailsWidget();

    void setDate(const QDate &date);

private:
    Ui::ReportDetailsWidget *ui;
    QDate m_date;

    void setupDelegates();
    int insertRow();
    void removeLastRow();
    QStringList availableGroups(const QString &currentGroup) const;
    bool saveToDatabase() const;
    AbsenteesItemDelegate *absenteesItemDelegate() const;
    GroupsComboBoxDelegate *groupsComboBoxDelegate() const;
    //СДЕЛАТЬ ПОТОМ ЧТОБЫ КОМБОБОКСЫ ОБНОВЛЯЛИСЬ ПРИ УДАЛЕНИИ ЭЛЕМЕНТОВ ИЗ СПИСКА
    //void updateComboBoxes();

signals:
    void rowInserted(int newRowIndex);
    void saveClicked(const QDate &date);

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
