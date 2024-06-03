#ifndef GROUPSCOMBOBOXDELEGATE_H
#define GROUPSCOMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class GroupsComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit GroupsComboBoxDelegate(QObject* parent);

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

signals:
    void groupChanged(const QString &text);
    void groupIndexChanged(int groupIndex);

private slots:
    void onComboBoxTextChanged(const QString &text);
};

#endif // GROUPSCOMBOBOXDELEGATE_H
