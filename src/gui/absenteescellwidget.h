#ifndef ABSENTEESCELLWIDGET_H
#define ABSENTEESCELLWIDGET_H

#include "labelwithbuttonwidget.h"

class AbsenteesCellWidget : public LabelWithButtonWidget
{
    Q_OBJECT
public:
    explicit AbsenteesCellWidget(int groupId, QWidget *parent);

    static QHash<int, QStringList> &absentees();

private:
    int m_groupId;
    static QHash<int, QStringList> m_absentees;

    QStringList labelToList() const;

signals:
    void absenteesSaved(const QStringList &names);

private slots:
    void onButtonClicked();
    void onAbsenteesSaved(const QStringList &names);
};

#endif // ABSENTEESCELLWIDGET_H
