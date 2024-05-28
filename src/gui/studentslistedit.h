#ifndef STUDENTSLISTEDIT_H
#define STUDENTSLISTEDIT_H

#include "listeditwidget.h"

class StudentsListEdit : public ListEditWidget
{
    Q_OBJECT
public:
    explicit StudentsListEdit(const QString &group, QWidget *parent = nullptr);

private:
    QString m_group;

    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;
};

#endif // STUDENTSLISTEDIT_H
