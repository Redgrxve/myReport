#ifndef EDITABLELISTWIDGET_H
#define EDITABLELISTWIDGET_H

#include <QWidget>
#include <QListWidget>

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

    virtual bool addToDatabase(const QString &item) = 0;
    virtual bool deleteFromDatabase(const QString &item) = 0;

    void addNewItem();
    void removeSelectedItem();
    QListWidget *listWidget() const;

protected slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
};

#endif // EDITABLELISTWIDGET_H
