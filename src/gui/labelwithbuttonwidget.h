#ifndef LABELWITHBUTTONWIDGET_H
#define LABELWITHBUTTONWIDGET_H

#include <QLabel>
#include <QWidget>

namespace Ui {
class LabelWithButtonWidget;
}

class LabelWithButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LabelWithButtonWidget(QWidget *parent = nullptr);
    ~LabelWithButtonWidget();

    QLabel *label() const;

private:
    Ui::LabelWithButtonWidget *ui;

signals:
    void buttonClicked();

private slots:
    void onButtonClicked();
};

#endif // LABELWITHBUTTONWIDGET_H
