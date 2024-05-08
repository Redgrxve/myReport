#include "mainwindow.h"
#include "starterdialog.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../../db/database.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, "Ошибка",
                                       "Не удалось подключиться к базе данных."
                                       "\nПопробуйте перезапустить приложение");
        return -1;
    }
    QSqlQuery query;
    if (!query.exec("SELECT fullName FROM teachers")) {
        QMessageBox::critical(nullptr, "Ошибка",
                              "Не удалось подключиться к базе данных."
                              "\nПопробуйте перезапустить приложение");
        return -1;
    }
    StarterDialog starterDialog(&query, &db);
    QObject::connect(&starterDialog, SIGNAL(accepted()), &starterDialog, SLOT(createMainWindow()));
    QObject::connect(&starterDialog, SIGNAL(rejected()), &a, SLOT(quit()));
    starterDialog.show();
    return a.exec();
}
