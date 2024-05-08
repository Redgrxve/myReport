#ifndef STARTERDIALOG_H
#define STARTERDIALOG_H

#include <QDialog>

class QSqlDatabase;
class QSqlQuery;

namespace Ui {
class StarterDialog;
}

class StarterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StarterDialog(QSqlQuery *selectNamesQuery, QSqlDatabase *db, QWidget *parent = nullptr);
    ~StarterDialog();

private:
    Ui::StarterDialog *ui;
    QSqlDatabase *m_db;

    void clearLineEdits() const;
    void fillComboBox(QSqlQuery *queryResult) const;
    bool writeNameToDatabase(const QString &fullName);

public slots:
    void createMainWindow() const;

private slots:
    void onCheckBoxToggled(bool checked) const;
    void onAddClicked();
    void onComboBoxChanged() const;
};

#endif // STARTERDIALOG_H
