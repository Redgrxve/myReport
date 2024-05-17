#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "groupslistedit.h"
#include "subjectslistedit.h"

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
    GroupsListEdit *groupsWidget = new GroupsListEdit;
    groupsWidget->show();
}

void MainWindow::onDisciplinesTriggered()
{
    SubjectsListEdit *disciplinesWidget = new SubjectsListEdit;
    disciplinesWidget->show();
}

