#include "groupscomboboxdelegate.h"
#include "databasemanager.h"
#include "groupscombobox.h"

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

    GroupsComboBox *comboBox = new GroupsComboBox(m_groups,
                                                  parent);
    connect(comboBox, &GroupsComboBox::currentTextChanged,
            this, &GroupsComboBoxDelegate::onComboBoxTextChanged);
    return comboBox;
}

void GroupsComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    GroupsComboBox *comboBox = static_cast<GroupsComboBox*>(editor);
    connect(comboBox, &GroupsComboBox::currentTextChanged,
            this, &GroupsComboBoxDelegate::onComboBoxTextChanged);
    int itemIndex = comboBox->findText(data);
    if (itemIndex != -1) {
        comboBox->setCurrentIndex(itemIndex);
        //emit comboBox->currentTextChanged(comboBox->itemText(itemIndex));
    }
}

void GroupsComboBoxDelegate::setModelData(QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const
{
    GroupsComboBox *comboBox = static_cast<GroupsComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void GroupsComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void GroupsComboBoxDelegate::onComboBoxTextChanged(const QString &text)
{
    emit groupChanged(text);
    emit groupIndexChanged(DatabaseManager::instance()->selectIdFromGroups(text));
}
