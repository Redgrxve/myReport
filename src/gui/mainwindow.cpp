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

    m_windowManager = new WindowManager;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_windowManager;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_windowManager->closeAndDeleteAll();

    QMainWindow::closeEvent(event);
}

void MainWindow::onGroupsTriggered()
{
    GroupsListEdit *groupsWidget = new GroupsListEdit(m_windowManager);
    groupsWidget->show();
    m_windowManager->add(groupsWidget);
}

void MainWindow::onDisciplinesTriggered()
{
    SubjectsListEdit *subjectsWidget = new SubjectsListEdit;
    subjectsWidget->show();
    m_windowManager->add(subjectsWidget);
}

