#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include "databasemanager.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    ui->signupGroupBox->hide();
    ui->onSignupLabel->hide();

    connect(ui->newUserCheckBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxToggled(bool)));
    connect(ui->loginButton, SIGNAL(clicked()), this, SLOT(onLoginClicked()));
    connect(ui->signupButton, SIGNAL(clicked()), this, SLOT(onSignupClicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::createMainWindow()
{
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
}

void LoginDialog::onCheckBoxToggled(bool checked)
{
    ui->signupGroupBox->setVisible(checked);
    ui->onSignupLabel->hide();
}

void LoginDialog::onLoginClicked()
{
    if (ui->loginLineEdit->text().isEmpty()
        || ui->loginPasswordLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                             tr("Необходимо заполнить все поля"));
        return;
    }

    QString login = ui->loginLineEdit->text();
    QString password = ui->loginPasswordLineEdit->text();
    QString registeredPassword = DatabaseManager::instance()->selectPasswordFromUsers(login);
    if (registeredPassword.isEmpty() || password != registeredPassword) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Неправильный логин или пароль"));
        return;
    }

    emit accepted();
    close();
}

void LoginDialog::onSignupClicked()
{
    if (ui->signupLoginLineEdit->text().isEmpty()
        || ui->signupPasswordLineEdit->text().isEmpty()
        || ui->repeatPasswordLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Необходимо заполнить все поля"));
        return;
    }

    if (ui->signupPasswordLineEdit->text()
        != ui->repeatPasswordLineEdit->text()) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Пароли должны совпадать"));
        return;
    }

    QString login = ui->signupLoginLineEdit->text();
    QString password = ui->signupPasswordLineEdit->text();
    if (!DatabaseManager::instance()->insertToUsers(login, password)) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Ошибка при регистрации."
                                 "\nВозможно, такой логин уже существует."
                                 "\nПопробуйте еще раз"));
        return;
    }

    ui->signupLoginLineEdit->clear();
    ui->signupPasswordLineEdit->clear();
    ui->repeatPasswordLineEdit->clear();
    ui->onSignupLabel->show();
}
