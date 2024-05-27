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

    bool verifyPassword(const QString &login,
                        const QString &password);

    bool storePasswordInDatabase(const QString &login,
                                 const QString &password);

    int userIdByLogin(const QString& login);
    void clearSignupLineEdits();

public slots:
    void createMainWindow();

private slots:
    void onCheckBoxToggled(bool checked);
    void onLoginClicked();
    void onSignupClicked();
};

#endif // LOGINDIALOG_H
