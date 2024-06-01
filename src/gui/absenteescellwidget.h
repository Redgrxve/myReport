#ifndef ABSENTEESCELLWIDGET_H
#define ABSENTEESCELLWIDGET_H

#include "labelwithbuttonwidget.h"

class AbsenteesCellWidget : public LabelWithButtonWidget
{
    Q_OBJECT
public:
    explicit AbsenteesCellWidget(int groupId,
                                 QWidget *parent);

private:
    int m_groupId;

private slots:
    void onButtonClicked();
};

#endif // ABSENTEESCELLWIDGET_H
