#include "groupscomboboxdelegate.h"
#include "absenteestablewidgetitem.h"
#include "groupscombobox.h"
#include "grouptablewidgetitem.h"

GroupsComboBoxDelegate::GroupsComboBoxDelegate(const QStringList &groups,
                                               QObject* parent)
    : QStyledItemDelegate(parent)
    , m_groups(groups)
{}

void GroupsComboBoxDelegate::setAvailableGroups(const QStringList &groups)
{
    m_groups = groups;
}

QWidget *GroupsComboBoxDelegate::createEditor(QWidget *parent,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{

    GroupsComboBox *editor = new GroupsComboBox(m_groups, parent);
    return editor;
}

void GroupsComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    auto comboBox = static_cast<GroupsComboBox*>(editor);
    int itemIndex = comboBox->findText(data);
    if (itemIndex != -1) {
        comboBox->setCurrentIndex(itemIndex);
    }
}

void GroupsComboBoxDelegate::setModelData(QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const
{
    auto comboBox = static_cast<GroupsComboBox*>(editor);
    auto tableWidget = static_cast<QTableWidget*>(model->parent());
    auto groupItem = static_cast<GroupTableWidgetItem*>(
        tableWidget->item(index.row(), index.column()));
    auto absenteesItem = static_cast<AbsenteesTableWidgetItem*>(
        tableWidget->item(index.row(), 1));

    QString data = comboBox->currentText();
    groupItem->setGroup(data);
    if (model->data(index, Qt::EditRole) != data)
        absenteesItem->clear();

    model->setData(index, data, Qt::EditRole);
}

void GroupsComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
