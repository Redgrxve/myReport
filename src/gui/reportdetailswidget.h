#ifndef REPORTDETAILSWIDGET_H
#define REPORTDETAILSWIDGET_H

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

    //СДЕЛАТЬ ПОТОМ ЧТОБЫ КОМБОБОКСЫ ОБНОВЛЯЛИСЬ ПРИ УДАЛЕНИИ ЭЛЕМЕНТОВ ИЗ СПИСКА
    void updateComboBoxes();

    void setupDelegates();

private slots:
    void onCalendarButtonClicked();
    void onDateSelected(const QDate &date);
};

#endif // REPORTDETAILSWIDGET_H
