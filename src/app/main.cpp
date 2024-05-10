#include "starterdialog.h"
#include "databasemanager.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseManager* dbManager = DatabaseManager::instance();
    if (!dbManager->connect()) {
        QMessageBox::critical(nullptr, "Ошибка",
                                       "Не удалось подключиться к базе данных."
                                       "\nПопробуйте перезапустить приложение");
        return -1;
    }

    StarterDialog starterDialog;
    QObject::connect(&starterDialog, SIGNAL(accepted()), &starterDialog, SLOT(createMainWindow()));
    QObject::connect(&starterDialog, SIGNAL(rejected()), &a, SLOT(quit()));
    starterDialog.show();
    return a.exec();
}
