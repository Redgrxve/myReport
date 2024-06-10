#include "grouptablewidgetitem.h"
#include "databasemanager.h"

GroupTableWidgetItem::GroupTableWidgetItem(int groupId)
    : QTableWidgetItem()
    , m_groupId(groupId)
{
    setTextAlignment(Qt::AlignCenter);
}

int GroupTableWidgetItem::groupId() const
{
    return m_groupId;
}

void GroupTableWidgetItem::setGroupId(int id)
{
    m_groupId = id;
}

void GroupTableWidgetItem::setGroup(const QString &group)
{
    int id = DatabaseManager::instance()->selectIdFromGroups(group);
    m_groupId = id;
}
