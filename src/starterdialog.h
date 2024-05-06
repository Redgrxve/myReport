#ifndef STARTERDIALOG_H
#define STARTERDIALOG_H

#include <QDialog>

namespace Ui {
class StarterDialog;
}

class StarterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StarterDialog(QWidget *parent = nullptr);
    ~StarterDialog();

private:
    Ui::StarterDialog *ui;

private slots:
    void onCheckBoxToggled(bool checked);
};

#endif // STARTERDIALOG_H
