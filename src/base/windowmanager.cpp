#include "windowmanager.h"

WindowManager::WindowManager() {}

WindowManager::~WindowManager()
{

}

void WindowManager::add(QWidget *widget)
{
    if (m_openedWidgets.contains(widget)) {
        widget->focusWidget();
        return;
    }

    m_openedWidgets.push(widget);
}

void WindowManager::closeAll()
{
    while (m_openedWidgets.size() > 0) {
        auto widget = m_openedWidgets.pop();
        widget->close();
    }
}

void WindowManager::closeAndDeleteAll()
{
    while (m_openedWidgets.size() > 0) {
        auto widget = m_openedWidgets.pop();
        widget->close();
        widget->deleteLater();
    }
}
