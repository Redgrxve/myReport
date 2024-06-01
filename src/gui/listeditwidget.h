#ifndef LISTEDITWIDGET_H
#define LISTEDITWIDGET_H

#include <QWidget>
#include <QListWidget>

namespace Ui {
class ListEditWidget;
}

class ListEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListEditWidget(QWidget *parent = nullptr);
    virtual ~ListEditWidget();

    bool isItemInList(const QString &text) const;

protected:
    virtual bool addToDatabase(const QString &item) = 0;
    virtual bool deleteFromDatabase(const QString &item) = 0;

    virtual void addNewItem();
    virtual void removeSelectedItem();

    QListWidget *listWidget() const;

private:
    Ui::ListEditWidget *ui;

protected slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
};

#endif // LISTEDITWIDGET_H
