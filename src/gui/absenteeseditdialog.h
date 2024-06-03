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
    explicit AbsenteesEditDialog(int groupId,
                                 const QStringList &names,
                                 QWidget *parent = nullptr);
    ~AbsenteesEditDialog();

private:
    Ui::AbsenteesEditDialog *ui;
    int m_groupId;

signals:
    void absenteesSaved(const QStringList &absentees);

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onStudentSelected(const QString &name);
    void onSaveClicked();
};

#endif // ABSENTEESEDITDIALOG_H
