#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <FramelessHelper/Widgets/framelessmainwindow.h>

namespace Ui
{
class MainWindow;
}
using FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessMainWindow);
class MainWindow : public FramelessMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
