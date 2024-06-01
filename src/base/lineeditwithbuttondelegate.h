#ifndef LINEEDITWITHBUTTONDELEGATE_H
#define LINEEDITWITHBUTTONDELEGATE_H

#include <QStyledItemDelegate>

class LineEditWithButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit LineEditWithButtonDelegate(QObject *parent = nullptr);

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
};

#endif // LINEEDITWITHBUTTONDELEGATE_H
