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

    void clearLineEdits() const;

public slots:
    void createMainWindow() const;

private slots:
    void onCheckBoxToggled(bool checked) const;
    void onAddClicked();
    void onComboBoxChanged() const;
};

#endif // STARTERDIALOG_H
