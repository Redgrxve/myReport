#include "labelwithbuttonwidget.h"
#include "ui_labelwithbuttonwidget.h"

LabelWithButtonWidget::LabelWithButtonWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LabelWithButtonWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

LabelWithButtonWidget::~LabelWithButtonWidget()
{
    delete ui;
}

QLabel *LabelWithButtonWidget::label() const
{
    return ui->label;
}

void LabelWithButtonWidget::onButtonClicked()
{
    emit buttonClicked();
}
