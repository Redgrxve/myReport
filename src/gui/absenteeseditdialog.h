#ifndef ABSENTEESEDITDIALOG_H
#define ABSENTEESEDITDIALOG_H

#include <QDialog>

namespace Ui {
class AbsenteesEditDialog;
}

class AbsenteesEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AbsenteesEditDialog(int groupId, QWidget *parent = nullptr);
    ~AbsenteesEditDialog();

private:
    Ui::AbsenteesEditDialog *ui;
    int m_groupId;

private slots:
    void onAddButtonClicked();
};

#endif // ABSENTEESEDITDIALOG_H
