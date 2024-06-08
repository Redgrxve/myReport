#ifndef GROUPSCOMBOBOXDELEGATE_H
#define GROUPSCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class GroupsComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit GroupsComboBoxDelegate(const QStringList &groups,
                                    QObject* parent);

    void setAvailableGroups(const QStringList &groups);

private:
    QStringList m_groups;

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor,
                       const QModelIndex &index) const override;

    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // GROUPSCOMBOBOXDELEGATE_H
