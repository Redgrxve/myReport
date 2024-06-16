#ifndef REPORTDETAILSWIDGET_H
#define REPORTDETAILSWIDGET_H

#include <QDate>
#include <QWidget>

class AbsenteesItemDelegate;
class GroupsComboBoxDelegate;
class GroupTableWidgetItem;
class AbsenteesTableWidgetItem;

namespace Ui {
class ReportDetailsWidget;
}

class ReportDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportDetailsWidget(QWidget *parent = nullptr);
    ~ReportDetailsWidget();

    bool save(bool forceSave = false);
    void setDate(const QDate &date);
    void setupFromDatabase(const QDate &date);

private:
    Ui::ReportDetailsWidget *ui;
    QDate m_date;
    bool m_isSaved = true;

    void setupDelegates();
    int insertRow();
    void removeLastRow();
    QStringList availableGroups(const QString &currentGroup) const;
    bool isReportInDatabase();
    bool writeToDatabase();

    AbsenteesItemDelegate *absenteesItemDelegate() const;
    GroupsComboBoxDelegate *groupsComboBoxDelegate() const;
    GroupTableWidgetItem *groupTableItem(int row, int column) const;
    AbsenteesTableWidgetItem *absenteesTableItem(int row, int column) const;

    void closeEvent(QCloseEvent *event) override;

    //СДЕЛАТЬ ПОТОМ ЧТОБЫ КОМБОБОКСЫ ОБНОВЛЯЛИСЬ ПРИ УДАЛЕНИИ ЭЛЕМЕНТОВ ИЗ СПИСКА
    //void updateComboBoxes();

signals:
    void saveClicked(const QDate &date);

public slots:
    void onReportSelected(const QDate &date);

private slots:
    void openCalendar();
    void onDateSelected(const QDate &date);
    void onCellEdit(int row, int column);
    void onSaveClicked();
};

#endif // REPORTDETAILSWIDGET_H
