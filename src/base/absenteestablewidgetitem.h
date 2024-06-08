#ifndef ABSENTEESTABLEWIDGETITEM_H
#define ABSENTEESTABLEWIDGETITEM_H

#include <QTableWidgetItem>

class AbsenteesTableWidgetItem : public QTableWidgetItem
{
public:
    AbsenteesTableWidgetItem();

    void clear();
    const QStringList &absentees() const;
    void setAbsentees(const QStringList &list);
    void addToAbsentees(const QString &name);

private:
    QStringList m_absentees;
};

#endif // ABSENTEESTABLEWIDGETITEM_H
