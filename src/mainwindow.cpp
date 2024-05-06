#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "starterdialog.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    StarterDialog* starterDialog = new StarterDialog(this);
    connect(starterDialog, SIGNAL(accepted()), this, SLOT(onStarterDialogAccepted()));
    connect(starterDialog, SIGNAL(rejected()), this, SLOT(onStarterDialogRejected()));
    starterDialog->exec();

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStarterDialogAccepted()
{

}

void MainWindow::onStarterDialogRejected()
{
    QMessageBox::information(this, "rejected", "rejected");
}
