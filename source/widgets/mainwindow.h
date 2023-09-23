#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <FramelessHelper/Widgets/framelessmainwindow.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>

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
    ~MainWindow() override;

  private:
    Ui::MainWindow* ui;

    QAbstractItemModel* _bottom_left_menu_model;
    QAbstractItemModel* _vtk_shapes_model;

};

#endif  // MAINWINDOW_H
