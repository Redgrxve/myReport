#ifndef GROUPSLISTWIDGET_H
#define GROUPSLISTWIDGET_H

#include "editablelistwidget.h"

class GroupsListWidget : public EditableListWidget
{
    Q_OBJECT

public:
    explicit GroupsListWidget(QWidget* parent = nullptr);

private:
    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;
};

#endif // GROUPSLISTWIDGET_H
