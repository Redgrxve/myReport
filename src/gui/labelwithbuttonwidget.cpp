#include "labelwithbuttonwidget.h"
#include "ui_labelwithbuttonwidget.h"

LabelWithButtonWidget::LabelWithButtonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LabelWithButtonWidget)
{
    ui->setupUi(this);
}

LabelWithButtonWidget::~LabelWithButtonWidget()
{
    delete ui;
}

QLabel *LabelWithButtonWidget::label() const
{
    return ui->label;
}
