#include "absenteescellwidget.h"
#include "absenteeseditdialog.h"

#include <QMessageBox>

QHash<int, QStringList> AbsenteesCellWidget::m_absentees;

AbsenteesCellWidget::AbsenteesCellWidget(int groupId, QWidget *parent)
    : LabelWithButtonWidget(parent)
    , m_groupId(groupId)
{
    connect(this, &AbsenteesCellWidget::buttonClicked,
            this, &AbsenteesCellWidget::onButtonClicked);
}

QStringList AbsenteesCellWidget::labelToList() const
{
    QString names = label()->text();
    if (!names.isEmpty())
        return names.split(", ");

    return QStringList();
}

QHash<int, QStringList> AbsenteesCellWidget::absentees()
{
    return m_absentees;
}

void AbsenteesCellWidget::onButtonClicked()
{
    if (m_groupId == -1) {
        QMessageBox::warning(this, tr("Внимание"), tr("Необходимо указать группу"));
        return;
    }

    AbsenteesEditDialog absenteesDialog(m_groupId, m_absentees[m_groupId], this);
    connect(&absenteesDialog, &AbsenteesEditDialog::absenteesSaved,
            this, &AbsenteesCellWidget::onAbsenteesSaved);
    absenteesDialog.exec();
}

void AbsenteesCellWidget::onAbsenteesSaved(const QStringList &names)
{
    label()->setText(names.join(", "));
    m_absentees[m_groupId] = names;
    emit absenteesSaved(names);
}
