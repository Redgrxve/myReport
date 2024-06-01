#include "absenteescellwidget.h"
#include "studentslistedit.h"

AbsenteesCellWidget::AbsenteesCellWidget(int groupId, QWidget *parent)
    : LabelWithButtonWidget(parent)
    , m_groupId(groupId)
{
    connect(this, SIGNAL(buttonClicked()), this, SLOT(onButtonClicked()));
}

void AbsenteesCellWidget::onButtonClicked()
{
    StudentsListEdit *studentsList = new StudentsListEdit(m_groupId);
    studentsList->show();
}
