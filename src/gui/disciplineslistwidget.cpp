#include "disciplineslistwidget.h"
#include "databasemanager.h"

DisciplinesListWidget::DisciplinesListWidget(QWidget *parent)
    : EditableListWidget(parent)
{
    setWindowTitle("Список дисциплин");
    listWidget()->addItems(DatabaseManager::instance()->selectFromDisciplines());
}

bool DisciplinesListWidget::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToDisciplines(item);
}

bool DisciplinesListWidget::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromDisciplines(item);
}

