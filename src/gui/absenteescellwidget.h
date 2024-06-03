#ifndef ABSENTEESCELLWIDGET_H
#define ABSENTEESCELLWIDGET_H

#include "labelwithbuttonwidget.h"

class AbsenteesCellWidget : public LabelWithButtonWidget
{
    Q_OBJECT
public:
    explicit AbsenteesCellWidget(int groupId, QWidget *parent);

private:
    int m_groupId;

    QStringList labelToList() const;

signals:
    void absenteesSaved(const QStringList &names);

private slots:
    void onButtonClicked();
    void onAbsenteesSaved(const QStringList &names);
};

#endif // ABSENTEESCELLWIDGET_H
