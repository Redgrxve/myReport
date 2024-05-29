#ifndef STUDENTSLISTEDIT_H
#define STUDENTSLISTEDIT_H

#include "listeditwidget.h"

class StudentsListEdit : public ListEditWidget
{
    Q_OBJECT
public:
    explicit StudentsListEdit(int groupId, QWidget *parent = nullptr);

private:
    int m_groupId;

    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;
};

#endif // STUDENTSLISTEDIT_H
