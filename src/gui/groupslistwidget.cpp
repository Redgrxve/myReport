#include "groupslistwidget.h"
#include "ui_groupslistwidget.h"

GroupsListWidget::GroupsListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GroupsListWidget)
{
    ui->setupUi(this);
}

GroupsListWidget::~GroupsListWidget()
{
    delete ui;
}
