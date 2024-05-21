#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;

public slots:
    void createMainWindow();

private slots:
    void onCheckBoxToggled(bool checked);
    void onLoginClicked();
    void onSignupClicked();
};

#endif // LOGINDIALOG_H
