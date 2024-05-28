#ifndef GROUPSLISTEDIT_H
#define GROUPSLISTEDIT_H

#include "listeditwidget.h"

class GroupsListEdit : public ListEditWidget
{
    Q_OBJECT

public:
    explicit GroupsListEdit(QWidget* parent = nullptr);

private:
    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;

private slots:
    void onItemDoubleClicked(QListWidgetItem* item);
};

#endif // GROUPSLISTEDIT_H
