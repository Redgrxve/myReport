#include "absenteesitemdelegate.h"
#include "absenteescellwidget.h"

AbsenteesItemDelegate::AbsenteesItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void AbsenteesItemDelegate::setGroupId(int id)
{
    m_groupId = id;
}

QWidget *AbsenteesItemDelegate::createEditor(QWidget *parent,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index) const
{
    AbsenteesCellWidget *absenteesWidget = new AbsenteesCellWidget(m_groupId, parent);
    return absenteesWidget;
}

void AbsenteesItemDelegate::setEditorData(QWidget *editor,
                                          const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    auto absenteesWidget = static_cast<AbsenteesCellWidget*>(editor);
    absenteesWidget->label()->setText(data);
}

void AbsenteesItemDelegate::setModelData(QWidget *editor,
                                         QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    auto absenteesWidget = static_cast<AbsenteesCellWidget*>(editor);
    QString data = absenteesWidget->label()->selectedText();
    model->setData(index, data, Qt::EditRole);
}

void AbsenteesItemDelegate::updateEditorGeometry(QWidget *editor,
                                                 const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
