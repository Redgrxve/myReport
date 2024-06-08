#include "absenteesitemdelegate.h"
#include "absenteescellwidget.h"
#include "absenteestablewidgetitem.h"
#include "grouptablewidgetitem.h"

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
    auto tableWidget = static_cast<QTableWidget*>(index.model()->parent());
    auto groupItem = static_cast<GroupTableWidgetItem*>(
        tableWidget->item(index.row(), 0));
    auto absenteesItem = static_cast<AbsenteesTableWidgetItem*>(
        tableWidget->item(index.row(), 1));

    AbsenteesCellWidget *editor = new AbsenteesCellWidget(groupItem->groupId(), parent);
    editor->setAbsentees(absenteesItem->absentees());

    editor->setProperty("model", QVariant::fromValue(const_cast<QAbstractItemModel*>(index.model())));
    editor->setProperty("index", QVariant::fromValue(index));

    connect(editor, &AbsenteesCellWidget::absenteesSaved,
            this, &AbsenteesItemDelegate::onAbsenteesSaved);
    return editor;
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
    auto tableWidget = static_cast<QTableWidget*>(model->parent());
    auto absenteesItem = static_cast<AbsenteesTableWidgetItem*>(
        tableWidget->item(index.row(), index.column()));

    QStringList absentees = absenteesWidget->absentees();
    QString data = absenteesWidget->label()->text();
    absenteesItem->setAbsentees(absentees);
    model->setData(index, data, Qt::EditRole);
}

void AbsenteesItemDelegate::updateEditorGeometry(QWidget *editor,
                                                 const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void AbsenteesItemDelegate::paint(QPainter *painter,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    opt.text.clear();

    QStyledItemDelegate::paint(painter, opt, index);
}

void AbsenteesItemDelegate::onAbsenteesSaved(QWidget *editor)
{
    QAbstractItemModel *model = editor->property("model").value<QAbstractItemModel*>();
    QModelIndex index = editor->property("index").value<QModelIndex>();
    if (!model) {
        qDebug() << "Model is nullptr";
        return;
    }

    setModelData(editor, model, index);
}

