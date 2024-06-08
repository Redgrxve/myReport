#include "absenteescellwidget.h"
#include "absenteeseditdialog.h"

#include <QMessageBox>

AbsenteesCellWidget::AbsenteesCellWidget(int groupId, QWidget *parent)
    : LabelWithButtonWidget(parent)
    , m_groupId(groupId)
{
    connect(this, &AbsenteesCellWidget::buttonClicked,
            this, &AbsenteesCellWidget::onButtonClicked);
}

void AbsenteesCellWidget::clear()
{
    m_absentees.clear();
    label()->clear();
}

QStringList AbsenteesCellWidget::labelToList() const
{
    QString names = label()->text();
    if (!names.isEmpty())
        return names.split(", ");

    return QStringList();
}

const QStringList &AbsenteesCellWidget::absentees() const
{
    return m_absentees;
}

void AbsenteesCellWidget::setAbsentees(const QStringList &list)
{
    m_absentees = list;
}

void AbsenteesCellWidget::onButtonClicked()
{
    if (m_groupId == -1) {
        QMessageBox::warning(this, tr("Внимание"), tr("Необходимо указать группу"));
        return;
    }

    AbsenteesEditDialog absenteesDialog(m_groupId, m_absentees, this);
    connect(&absenteesDialog, &AbsenteesEditDialog::absenteesSaved,
            this, &AbsenteesCellWidget::onAbsenteesSaved);
    absenteesDialog.exec();
}

void AbsenteesCellWidget::onAbsenteesSaved(const QStringList &names)
{
    label()->setText(names.join(", "));
    m_absentees = names;
    emit absenteesSaved(this);
}
