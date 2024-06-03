#ifndef STUDENTSSELECTDIALOG_H
#define STUDENTSSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class StudentsSelectDialog;
}

class StudentsSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StudentsSelectDialog(int groupId, QWidget *parent = nullptr);
    ~StudentsSelectDialog();

private:
    Ui::StudentsSelectDialog *ui;
    int m_groupId;
};

#endif // STUDENTSSELECTDIALOG_H
