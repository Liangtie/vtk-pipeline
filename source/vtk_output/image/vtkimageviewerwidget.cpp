#include "vtkimageviewerwidget.h"
#include "ui_vtkimageviewerwidget.h"

VtkImageViewerWidget::VtkImageViewerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VtkImageViewerWidget)
{
    ui->setupUi(this);
}

VtkImageViewerWidget::~VtkImageViewerWidget()
{
    delete ui;
}
