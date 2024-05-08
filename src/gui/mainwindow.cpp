#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>

MainWindow::MainWindow(QSqlDatabase *db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_db(db)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

