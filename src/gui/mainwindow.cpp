#include "groupslistwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onGroupsTriggered()
{
    GroupsListWidget* groupsWidget = new GroupsListWidget();
    groupsWidget->show();
}

