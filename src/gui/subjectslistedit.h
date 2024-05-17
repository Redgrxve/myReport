#ifndef SUBJECTSLISTEDIT_H
#define SUBJECTSLISTEDIT_H

#include "listeditwidget.h"

class SubjectsListEdit : public ListEditWidget
{
    Q_OBJECT

public:
    explicit SubjectsListEdit(QWidget *parent = nullptr);

private:
    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;
};

#endif // SUBJECTSLISTEDIT_H
