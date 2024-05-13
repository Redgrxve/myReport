#ifndef EDITABLELISTWIDGET_H
#define EDITABLELISTWIDGET_H

#include <QWidget>

namespace Ui {
class EditableListWidget;
}

class EditableListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditableListWidget(QWidget *parent = nullptr);
    virtual ~EditableListWidget();

    bool isItemInList(const QString &text) const;

protected:
    Ui::EditableListWidget *ui;

    virtual void addNewItem();
    virtual void removeSelectedItem();

protected slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
};

#endif // EDITABLELISTWIDGET_H
