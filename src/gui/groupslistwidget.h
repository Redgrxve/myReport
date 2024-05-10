#ifndef GROUPSLISTWIDGET_H
#define GROUPSLISTWIDGET_H

#include <QWidget>

namespace Ui {
class GroupsListWidget;
}

class GroupsListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GroupsListWidget(QWidget *parent = nullptr);
    ~GroupsListWidget();

private:
    Ui::GroupsListWidget *ui;
};

#endif // GROUPSLISTWIDGET_H
