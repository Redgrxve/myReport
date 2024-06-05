#ifndef REPORTLISTITEMWIDGET_H
#define REPORTLISTITEMWIDGET_H

#include <QWidget>
#include <QDate>

namespace Ui {
class ReportListItemWidget;
}

class ReportListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportListItemWidget(QWidget *parent = nullptr);
    ~ReportListItemWidget();

    void setDate(const QDate &date);
    QDate date() const;

private:
    Ui::ReportListItemWidget *ui;
    QDate m_date;
};

#endif // REPORTLISTITEMWIDGET_H
