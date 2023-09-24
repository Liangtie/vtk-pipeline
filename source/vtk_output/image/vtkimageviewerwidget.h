#ifndef VTKIMAGEVIEWERWIDGET_H
#define VTKIMAGEVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class VtkImageViewerWidget;
}

class VtkImageViewerWidget : public QWidget
{
    Q_OBJECT

  public:
    explicit VtkImageViewerWidget(QWidget *parent = nullptr);
    ~VtkImageViewerWidget();

  private:
    Ui::VtkImageViewerWidget *ui;
};

#endif // VTKIMAGEVIEWERWIDGET_H
