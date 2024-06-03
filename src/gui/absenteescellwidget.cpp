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

void AbsenteesCellWidget::onButtonClicked()
{
    if (m_groupId == -1) {
        QMessageBox::warning(this, tr("Внимание"), tr("Необходимо указать группу"));
        return;
    }
    AbsenteesEditDialog absenteesDialog(m_groupId, this);
    absenteesDialog.exec();
}
