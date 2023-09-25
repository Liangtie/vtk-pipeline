#include "vtksliceselectorwidget.h"
#include "ui_vtksliceselectorwidget.h"

vtkSliceSelectorWidget::vtkSliceSelectorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vtkSliceSelectorWidget)
{
    ui->setupUi(this);
}

vtkSliceSelectorWidget::~vtkSliceSelectorWidget()
{
    delete ui;
}
