#ifndef REPORTLISTITEMWIDGET_H
#define REPORTLISTITEMWIDGET_H

#include <QWidget>

namespace Ui {
class ReportListItemWidget;
}

class ReportListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportListItemWidget(QWidget *parent = nullptr);
    ~ReportListItemWidget();

private:
    Ui::ReportListItemWidget *ui;
};

#endif // REPORTLISTITEMWIDGET_H
