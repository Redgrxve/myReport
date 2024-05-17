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
    Ui::ListEditWidget *ui;

    virtual bool addToDatabase(const QString &item) = 0;
    virtual bool deleteFromDatabase(const QString &item) = 0;

    void addNewItem();
    void removeSelectedItem();
    QListWidget *listWidget() const;

protected slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
};

#endif // LISTEDITWIDGET_H
