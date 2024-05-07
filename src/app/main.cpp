#include "mainwindow.h"
#include "starterdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StarterDialog starterDialog;
    QObject::connect(&starterDialog, SIGNAL(accepted()), &starterDialog, SLOT(createMainWindow()));
    QObject::connect(&starterDialog, SIGNAL(rejected()), &a, SLOT(quit()));
    starterDialog.show();
    return a.exec();
}
