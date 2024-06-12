#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"
#include "databasemanager.h"
#include "passwordencrypt.h"
#include "appconfig.h"
#include "nospacevalidator.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setLineEditValidators();

    layout()->setSizeConstraint(QLayout::SetFixedSize);

    ui->signupGroupBox->hide();
    ui->onSignupLabel->hide();

    connect(ui->newUserCheckBox, &QCheckBox::toggled,
            this, &LoginDialog::onCheckBoxToggled);
    connect(ui->loginButton, &QPushButton::clicked,
            this, &LoginDialog::onLoginClicked);
    connect(ui->signupButton, &QPushButton::clicked,
            this, &LoginDialog::onSignupClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setLineEditValidators()
{
    NoSpaceValidator *validator = new NoSpaceValidator(this);
    ui->loginLineEdit->setValidator(validator);
    ui->signupLoginLineEdit->setValidator(validator);
    ui->loginPasswordLineEdit->setValidator(validator);
    ui->signupPasswordLineEdit->setValidator(validator);
    ui->repeatPasswordLineEdit->setValidator(validator);
}

bool LoginDialog::verifyPassword(const QString &login,
                                 const QString &password)
{
    const auto dbManager = DatabaseManager::instance();
    QByteArray storedHash = dbManager->selectPasswordFromUsers(login);
    QByteArray storedSalt = dbManager->selectSaltFromUsers(login);
    return PasswordEncrypt::compare(password, storedHash, storedSalt);
}

bool LoginDialog::storePasswordInDatabase(const QString &login,
                                          const QString &password)
{
    const auto dbManager = DatabaseManager::instance();
    QByteArray salt = PasswordEncrypt::generateSalt();
    QByteArray hashedPassword = PasswordEncrypt::generateHash(password, salt);
    return dbManager->insertToUsers(login, hashedPassword, salt);
}

void LoginDialog::clearSignupLineEdits()
{
    ui->signupLoginLineEdit->clear();
    ui->signupPasswordLineEdit->clear();
    ui->repeatPasswordLineEdit->clear();
}

void LoginDialog::createMainWindow()
{
    MainWindow* mainWindow = new MainWindow;
    mainWindow->show();
}

void LoginDialog::onCheckBoxToggled(bool checked)
{
    ui->signupGroupBox->setVisible(checked);
    ui->signupButton->setDefault(checked);
    ui->loginButton->setDefault(!checked);
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
    if (!verifyPassword(login, password)) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Неправильный логин или пароль"));
        return;
    }

    AppConfig::instance()->setUser(login);
    accept();
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
    if (!storePasswordInDatabase(login, password)) {
        QMessageBox::warning(this, tr("Внимание"),
                              tr("Ошибка при регистрации."
                                 "\nВозможно, такой логин уже существует."
                                 "\nПопробуйте еще раз"));
        return;
    }

    clearSignupLineEdits();
    ui->onSignupLabel->show();
}
