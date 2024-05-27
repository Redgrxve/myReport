#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QWidget>
#include <QStack>

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    void add(QWidget *widget);
    void closeAll();
    void closeAndDeleteAll();

private:
    QStack<QWidget*> m_openedWidgets;
};

#endif // WINDOWMANAGER_H
