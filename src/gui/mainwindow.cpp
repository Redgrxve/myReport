#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "groupslistedit.h"
#include "subjectslistedit.h"
#include "windowmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    windowManager = new WindowManager;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete windowManager;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    windowManager->closeAndDeleteAll();

    QMainWindow::closeEvent(event);
}

void MainWindow::onGroupsTriggered()
{
    GroupsListEdit *groupsWidget = new GroupsListEdit;
    groupsWidget->show();
    windowManager->add(groupsWidget);
}

void MainWindow::onDisciplinesTriggered()
{
    SubjectsListEdit *subjectsWidget = new SubjectsListEdit;
    subjectsWidget->show();
    windowManager->add(subjectsWidget);
}

