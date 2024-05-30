#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class CalendarDialog;
}

class CalendarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarDialog(QWidget *parent = nullptr);
    ~CalendarDialog();

private:
    Ui::CalendarDialog *ui;

signals:
    void dateSelected(QDate);

private slots:
    void onAccepted();
};

#endif // CALENDARDIALOG_H
