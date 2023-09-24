#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

#include <qabstractitemmodel.h>
#include <qabstractitemview.h>

namespace QtNodes
{
class DataFlowGraphModel;

}  // namespace QtNodes
using QtNodes::DataFlowGraphModel;
class VtkPipelineScene;
class VtkPipelineView;

namespace Ui
{
class MainWindow;
}
// using FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessMainWindow);
class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

  protected:
    void resizeEvent(QResizeEvent* event) override;

  private:
    void onWindowsSizeChanged();

    Ui::MainWindow* ui;
    QAbstractItemModel* _bottom_left_menu_model;
    QAbstractItemModel* _vtk_shapes_model;
    std::shared_ptr<DataFlowGraphModel> _dataFlowGraphModel;
    VtkPipelineScene* _vtkPipeLineScene;
    VtkPipelineView* _vtkPipeLineView;
};

#endif  // MAINWINDOW_H
