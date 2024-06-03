#ifndef STUDENTSSELECTDIALOG_H
#define STUDENTSSELECTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

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

signals:
    void studentSelected(const QString &name);

private slots:
    void onAccepted();
    void onItemDoubleClicked(QListWidgetItem *item);
};

#endif // STUDENTSSELECTDIALOG_H
