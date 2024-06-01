#include "lineeditwithbuttondelegate.h"
#include "labelwithbuttonwidget.h"

LineEditWithButtonDelegate::LineEditWithButtonDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

QWidget *LineEditWithButtonDelegate::createEditor(QWidget *parent,
                                                  const QStyleOptionViewItem &option,
                                                  const QModelIndex &index) const
{
    LabelWithButtonWidget *labelWithButton = new LabelWithButtonWidget(parent);
    return labelWithButton;
}

void LineEditWithButtonDelegate::setEditorData(QWidget *editor,
                                               const QModelIndex &index) const
{
    QString data = index.model()->data(index, Qt::EditRole).toString();
    auto labelWithButton = static_cast<LabelWithButtonWidget*>(editor);
    labelWithButton->label()->setText(data);
}

void LineEditWithButtonDelegate::setModelData(QWidget *editor,
                                              QAbstractItemModel *model,
                                              const QModelIndex &index) const
{
    auto labelWithButton = static_cast<LabelWithButtonWidget*>(editor);
    QString data = labelWithButton->label()->selectedText();
    model->setData(index, data, Qt::EditRole);
}

void LineEditWithButtonDelegate::updateEditorGeometry(QWidget *editor,
                                                      const QStyleOptionViewItem &option,
                                                      const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
