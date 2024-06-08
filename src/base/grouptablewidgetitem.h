#ifndef GROUPTABLEWIDGETITEM_H
#define GROUPTABLEWIDGETITEM_H

#include <QTableWidgetItem>

class GroupTableWidgetItem : public QTableWidgetItem
{
public:
    GroupTableWidgetItem(int groupId = -1);

    int groupId() const;
    void setGroupId(int id);
    void setGroup(const QString &group);

private:
    int m_groupId;
};

#endif // GROUPTABLEWIDGETITEM_H
