#ifndef ABSENTEESCELLWIDGET_H
#define ABSENTEESCELLWIDGET_H

#include "labelwithbuttonwidget.h"

class AbsenteesCellWidget : public LabelWithButtonWidget
{
    Q_OBJECT
public:
    explicit AbsenteesCellWidget(int groupId, QWidget *parent);

    void clear();

    const QStringList &absentees() const;
    void setAbsentees(const QStringList &list);

private:
    int m_groupId;
    QStringList m_absentees;

    QStringList labelToList() const;

signals:
    void absenteesSaved(QWidget *editor);

private slots:
    void onButtonClicked();
    void onAbsenteesSaved(const QStringList &names);
};

#endif // ABSENTEESCELLWIDGET_H
