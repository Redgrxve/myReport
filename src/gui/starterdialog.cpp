#include "starterdialog.h"
#include "mainwindow.h"
#include "nospacevalidator.h"
#include "ui_starterdialog.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

StarterDialog::StarterDialog(QSqlQuery *selectNamesQuery, QSqlDatabase *db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StarterDialog)
    , m_db(db)
{
    ui->setupUi(this);

    ui->newTeacherGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    fillComboBox(selectNamesQuery);
    if (ui->comboBox->count() == 0)
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    NoSpaceValidator *validator = new NoSpaceValidator(this);
    ui->lastNameLineEdit->setValidator(validator);
    ui->firstNameLineEdit->setValidator(validator);
    ui->patronymicLineEdit->setValidator(validator);

    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(onCheckBoxToggled(bool)));
    connect(ui->addButton, SIGNAL(clicked(bool)), this, SLOT(onAddClicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxChanged()));
}

StarterDialog::~StarterDialog()
{
    delete ui;
}

void StarterDialog::clearLineEdits() const
{
    ui->lastNameLineEdit->clear();
    ui->firstNameLineEdit->clear();
    ui->patronymicLineEdit->clear();
}

void StarterDialog::fillComboBox(QSqlQuery *queryResult) const
{
    while (queryResult->next()) {
        ui->comboBox->addItem(queryResult->value(0).toString());
    }
}

bool StarterDialog::writeNameToDatabase(const QString &fullName)
{
    QSqlQuery query;
    query.prepare("INSERT INTO teachers (fullName) VALUES (:name)");
    query.bindValue(":name", fullName);
    if (!query.exec()) {
        qDebug() << "Error executing query: " <<  query.lastError().text();
        return false;
    }

    qDebug() << "Row added successfully.";
    return true;
}

void StarterDialog::onCheckBoxToggled(bool checked) const
{
    ui->newTeacherGroupBox->setVisible(checked);
}

void StarterDialog::onAddClicked()
{
    if (ui->lastNameLineEdit->text().isEmpty()
        || ui->firstNameLineEdit->text().isEmpty()
        || ui->patronymicLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Внимание"),
                                   tr("Необходимо заполнить все поля"));
        return;
    }

    QString newTeacherName =
        ui->lastNameLineEdit->text() + " "
        + ui->firstNameLineEdit->text() + " "
        + ui->patronymicLineEdit->text();


    if (ui->comboBox->findText(newTeacherName) != -1) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, tr("Внимание"),
                                                                        tr("Такое ФИО уже присутствует в списке."
                                                                           "\nВы хотите его добавить?"));
        if (reply == QMessageBox::No) {
            clearLineEdits();
            return;
        }
    }

    if (!writeNameToDatabase(newTeacherName)) {
        QMessageBox::warning(this, tr("Внимание"),
                                   tr("Ошибка при добавлении нового преподавателя."
                                      "\nПопробуйте еще раз."));
        return;
    }

    ui->comboBox->addItem(newTeacherName);
    ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    clearLineEdits();
}

void StarterDialog::onComboBoxChanged() const
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void StarterDialog::createMainWindow() const
{
    MainWindow* mainWindow = new MainWindow(m_db);
    mainWindow->show();
}
