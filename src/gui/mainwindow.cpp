#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "groupslistedit.h"
#include "subjectslistedit.h"
#include "windowmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_windowManager(new WindowManager)
{
    ui->setupUi(this);

    connect(ui->reportDetailsWidget, &ReportDetailsWidget::saveClicked,
            ui->listWidget, &ReportsListWidget::onReportSaved);
    connect(ui->reportDetailsWidget, &ReportDetailsWidget::saveClicked,
            this, &MainWindow::onReportSaved);
    connect(ui->listWidget, &ReportsListWidget::reportSelected,
            ui->reportDetailsWidget, &ReportDetailsWidget::onReportSelected);
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

// void MainWindow::onDisciplinesTriggered()
// {
//     SubjectsListEdit *subjectsWidget = new SubjectsListEdit;
//     subjectsWidget->show();
//     m_windowManager->add(subjectsWidget);
// }

void MainWindow::onNewReportTriggered()
{
    ui->listWidget->addEmptyItem();
}

void MainWindow::onDeleteTriggered()
{
    ui->listWidget->deleteCurrentItem();
}

void MainWindow::onReportSaved(const QDate &date)
{
    QString dateString = date.toString("dd.MM.yyyy");
    ui->statusbar->showMessage(tr("Рапортичка с датой ") + dateString + tr(" сохранена"));
}

