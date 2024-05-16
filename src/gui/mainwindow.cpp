#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "groupslistwidget.h"
#include "disciplineslistwidget.h"

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
    GroupsListWidget *groupsWidget = new GroupsListWidget;
    groupsWidget->show();
}

void MainWindow::onDisciplinesTriggered()
{
    DisciplinesListWidget *disciplinesWidget = new DisciplinesListWidget;
    disciplinesWidget->show();
}

