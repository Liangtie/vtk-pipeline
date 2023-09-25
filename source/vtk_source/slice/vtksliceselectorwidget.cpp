#include <QFileDialog>
#include <QIntValidator>

#include "vtk_source/slice/vtksliceselectorwidget.h"

#include <qabstractbutton.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qvalidator.h>

#include "ui_vtksliceselectorwidget.h"
#include "utils/flat_style.hpp"
#include "vtksliceselectorwidget.h"

vtkSliceSelectorWidget::vtkSliceSelectorWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::vtkSliceSelectorWidget)
{
    ui->setupUi(this);

    setupFlatStyle(ui->btn_select_dir);
    connect(ui->btn_select_dir,
            &QAbstractButton::clicked,
            this,
            [this]()
            {
                auto dir = QFileDialog::getExistingDirectory(
                    nullptr, "Select the slice directory");
                if (!dir.isEmpty())
                    ui->edit_dir->setText(dir);
            });

    for (const auto& edit : {ui->edit_idx_end, ui->edit_idx_start}) {
        edit->setValidator(new QIntValidator);
    }

    for (const auto& edit :
         {ui->edit_idx_end, ui->edit_idx_start, ui->edit_dir, ui->edit_prefix})
    {
        connect(edit,
                &QLineEdit::textChanged,
                this,
                &vtkSliceSelectorWidget::data_changed);
    }
}

vtkSliceSelectorWidget::~vtkSliceSelectorWidget()
{
    delete ui;
}

void vtkSliceSelectorWidget::setDir(QString const& str)
{
    ui->edit_dir->setText(str);
}

void vtkSliceSelectorWidget::setPrefix(QString const& str)
{
    ui->edit_prefix->setText(str);
}

void vtkSliceSelectorWidget::setStartIdx(int idx)
{
    ui->edit_idx_start->setText(QString::number(idx));
}

void vtkSliceSelectorWidget::setEndIdx(int idx)
{
    ui->edit_idx_end->setText(QString::number(idx));
}

QString vtkSliceSelectorWidget::getDir() const
{
    return ui->edit_dir->text();
}

QString vtkSliceSelectorWidget::getPrefix() const
{
    return ui->edit_prefix->text();
}

int vtkSliceSelectorWidget::getStartIdx() const
{
    return ui->edit_idx_start->text().toInt();
}

int vtkSliceSelectorWidget::getEndIdx() const
{
    return ui->edit_idx_end->text().toInt();
}
