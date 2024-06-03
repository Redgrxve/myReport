#include "groupscomboboxdelegate.h"
#include "databasemanager.h"

#include <QComboBox>

GroupsComboBoxDelegate::GroupsComboBoxDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

QWidget *GroupsComboBoxDelegate::createEditor(QWidget *parent,
                                              const QStyleOptionViewItem &option,
                                              const QModelIndex &index) const
{

    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItems(DatabaseManager::instance()->selectNamesFromGroups());
    connect(comboBox, &QComboBox::currentTextChanged,
            this, &GroupsComboBoxDelegate::onComboBoxTextChanged);
    return comboBox;
}

void GroupsComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(data);
    if (itemIndex != -1) {
        comboBox->setCurrentIndex(itemIndex);
        emit comboBox->currentTextChanged(comboBox->itemText(itemIndex));
    }
}

void GroupsComboBoxDelegate::setModelData(QWidget *editor,
                                          QAbstractItemModel *model,
                                          const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
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
