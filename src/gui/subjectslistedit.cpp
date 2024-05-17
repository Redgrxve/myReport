#include "subjectslistedit.h"
#include "databasemanager.h"

SubjectsListEdit::SubjectsListEdit(QWidget *parent)
    : ListEditWidget(parent)
{
    setWindowTitle(tr("Список дисциплин"));
    listWidget()->addItems(DatabaseManager::instance()->selectFromDisciplines());
}

bool SubjectsListEdit::addToDatabase(const QString &item)
{
    return DatabaseManager::instance()->insertToDisciplines(item);
}

bool SubjectsListEdit::deleteFromDatabase(const QString &item)
{
    return DatabaseManager::instance()->deleteFromDisciplines(item);
}

