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

QStringList AbsenteesCellWidget::labelToList() const
{
    QString names = label()->text();
    if (!names.isEmpty())
        return names.split(", ");

    return QStringList();
}

void AbsenteesCellWidget::onButtonClicked()
{
    if (m_groupId == -1) {
        QMessageBox::warning(this, tr("Внимание"), tr("Необходимо указать группу"));
        return;
    }

    AbsenteesEditDialog absenteesDialog(m_groupId, labelToList(), this);
    connect(&absenteesDialog, &AbsenteesEditDialog::absenteesSaved,
            this, &AbsenteesCellWidget::onAbsenteesSaved);
    absenteesDialog.exec();
}

void AbsenteesCellWidget::onAbsenteesSaved(const QStringList &names)
{
    label()->setText(names.join(", "));
    emit absenteesSaved(names);
}
