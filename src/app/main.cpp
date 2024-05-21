#include "logindialog.h"
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

    LoginDialog loginDialog;
    QObject::connect(&loginDialog, SIGNAL(accepted()), &loginDialog, SLOT(createMainWindow()));
    loginDialog.show();
    return a.exec();
}
