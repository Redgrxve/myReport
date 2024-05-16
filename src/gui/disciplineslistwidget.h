#ifndef DISCIPLINESLISTWIDGET_H
#define DISCIPLINESLISTWIDGET_H

#include "editablelistwidget.h"

class DisciplinesListWidget : public EditableListWidget
{
    Q_OBJECT

public:
    explicit DisciplinesListWidget(QWidget *parent = nullptr);

private:
    bool addToDatabase(const QString &item) override;
    bool deleteFromDatabase(const QString &item) override;
};

#endif // DISCIPLINESLISTWIDGET_H
