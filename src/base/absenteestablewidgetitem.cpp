#include "absenteestablewidgetitem.h"

AbsenteesTableWidgetItem::AbsenteesTableWidgetItem()
    : QTableWidgetItem()
{}

void AbsenteesTableWidgetItem::clear()
{
    m_absentees.clear();
    setText("");
}

const QStringList &AbsenteesTableWidgetItem::absentees() const
{
    return m_absentees;
}

void AbsenteesTableWidgetItem::setAbsentees(const QStringList &list)
{
    m_absentees = list;
}

void AbsenteesTableWidgetItem::addToAbsentees(const QString &name)
{
    m_absentees.append(name);
}
