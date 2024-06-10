#ifndef ABSENTEESITEMDELEGATE_H
#define ABSENTEESITEMDELEGATE_H

#include <QStyledItemDelegate>

class AbsenteesItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit AbsenteesItemDelegate(QObject *parent = nullptr);

private:
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

     void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private slots:
    void onAbsenteesSaved(QWidget *editor);
};

#endif // ABSENTEESITEMDELEGATE_H
