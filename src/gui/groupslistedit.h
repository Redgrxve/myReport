#ifndef GROUPSLISTEDIT_H
#define GROUPSLISTEDIT_H

#include "listeditwidget.h"

class WindowManager;

class GroupsListEdit : public ListEditWidget
{
    Q_OBJECT

public:
    explicit GroupsListEdit(WindowManager* windowManager,
                            QWidget* parent = nullptr);

private:
    WindowManager* m_windowManager;

    void removeSelectedItem() override;
    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;

private slots:
    void onItemDoubleClicked(QListWidgetItem* item);
};

#endif // GROUPSLISTEDIT_H
