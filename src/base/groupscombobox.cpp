#include "groupscombobox.h"

GroupsComboBox::GroupsComboBox(const QStringList &items,
                               QWidget *parent)
    : QComboBox(parent)
{
    addItems(items);
}
