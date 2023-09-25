#ifndef VTKSLICESELECTORWIDGET_H
#define VTKSLICESELECTORWIDGET_H

#include <QWidget>

namespace Ui {
class vtkSliceSelectorWidget;
}

class vtkSliceSelectorWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit vtkSliceSelectorWidget(QWidget *parent = nullptr);
    ~vtkSliceSelectorWidget();

  private:
    Ui::vtkSliceSelectorWidget *ui;
};

#endif // VTKSLICESELECTORWIDGET_H
