#include <QFileDialog>

#include "vtkfilepathselectorwidget.h"

#include <qabstractbutton.h>
#include <qfiledialog.h>

#include "ui_vtkfilepathselectorwidget.h"
#include "utils/flat_style.hpp"

VtkFilePathSelectorWidget::VtkFilePathSelectorWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::VtkFilePathSelectorWidget)
{
    ui->setupUi(this);

    setupFlatStyle(ui->toolButton);

    connect(ui->toolButton,
            &QAbstractButton::clicked,
            this,
            [this]
            {
                auto fp =
                    QFileDialog::getOpenFileName(nullptr, "Selected a file");
                if (!fp.isEmpty()) {
                    ui->lineEdit->setText(fp);
                    emit filePathSelected(fp);
                }
            });
}

VtkFilePathSelectorWidget::~VtkFilePathSelectorWidget()
{
    delete ui;
}

void VtkFilePathSelectorWidget::setText(QString const& t)
{
    ui->lineEdit->setText(t);
}
