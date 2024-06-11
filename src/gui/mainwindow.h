#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class WindowManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WindowManager *m_windowManager;

    void closeEvent(QCloseEvent *event) override;

private slots:
    void onGroupsTriggered();
    void onDisciplinesTriggered();
    void onNewReportTriggered();
    void onDeleteTriggered();
};
#endif // MAINWINDOW_H
