#include "comboboxdelegate.h"
#include "databasemanager.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    QComboBox *comboBox = new QComboBox(parent);
    comboBox->addItems(DatabaseManager::instance()->selectNamesFromGroups());
    return comboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int itemIndex = comboBox->findText(data);
    if (itemIndex != -1)
        comboBox->setCurrentIndex(itemIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor,
                                    QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
