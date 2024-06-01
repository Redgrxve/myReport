#ifndef ABSENTEESITEMDELEGATE_H
#define ABSENTEESITEMDELEGATE_H

#include <QStyledItemDelegate>

class AbsenteesItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit AbsenteesItemDelegate(int groupId,
                                   QObject *parent = nullptr);

    void setGroupId(int id);

private:
    int m_groupId;

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

#endif // ABSENTEESITEMDELEGATE_H
