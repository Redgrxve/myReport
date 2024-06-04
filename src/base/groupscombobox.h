#ifndef GROUPSCOMBOBOX_H
#define GROUPSCOMBOBOX_H

#include <QComboBox>

class GroupsComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit GroupsComboBox(const QStringList &items,
                            QWidget *parent = nullptr);
};

#endif // GROUPSCOMBOBOX_H
