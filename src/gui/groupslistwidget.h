#ifndef GROUPSLISTWIDGET_H
#define GROUPSLISTWIDGET_H

#include "editablelistwidget.h"

class GroupsListWidget : public EditableListWidget
{
    Q_OBJECT

public:
    explicit GroupsListWidget(QWidget* parent = nullptr);
    ~GroupsListWidget();

private:
    void addNewItem() override;
    void removeSelectedItem() override;
};

#endif // GROUPSLISTWIDGET_H
