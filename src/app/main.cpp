#include "logindialog.h"
#include "databasemanager.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale locale = QLocale(QLocale::Russian, QLocale::Russia);
    QString translationsPath(QLibraryInfo::path(QLibraryInfo::TranslationsPath));
    QTranslator qtTranslator;
    if (qtTranslator.load(locale, "qt", "_", translationsPath))
        a.installTranslator(&qtTranslator);

    QTranslator qtBaseTranslator;
    if (qtBaseTranslator.load(locale, "qtbase", "_", translationsPath))
        a.installTranslator(&qtBaseTranslator);


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
