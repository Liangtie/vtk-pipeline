#include <memory>

#include "mainwindow.h"

#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <qabstractbutton.h>
#include <qabstractitemview.h>
#include <qframe.h>
#include <qicon.h>
#include <qlayoutitem.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qsizepolicy.h>
#include <qwidget.h>

#include "constraint/item_in_view.hpp"
#include "ui_mainwindow.h"
#include "vtk_pipeline/data_view_light_style.hpp"
#include "vtk_pipeline/vtk_pipeline_model.hpp"
#include "vtk_pipeline/vtk_pipeline_scene.hpp"
#include "vtk_pipeline/vtk_pipeline_view.hpp"
#include "widgets/bottom_left_menu/bottom_left_menu_model.hpp"
#include "widgets/bottom_left_menu/bottom_left_menu_view.hpp"

MainWindow::MainWindow(QWidget* parent)
    : FramelessMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _bottom_left_menu_model(new BottomLeftMenuModel(this))
{
    ui->setupUi(this);

    static const auto setupFlatStyle = [](QObject* obj)
    { obj->setProperty("flat", true); };

    // SECTION - Frameless
    {
        using namespace wangwenx190::FramelessHelper;
        auto helper = FRAMELESSHELPER_PREPEND_NAMESPACE(
            FramelessWidgetsHelper)::get(this);
        helper->setTitleBarWidget(ui->menu_top);

        helper->setSystemButton(ui->btn_close, Global::SystemButtonType::Close);
        helper->setSystemButton(ui->btn_min,
                                Global::SystemButtonType::Minimize);
        helper->setSystemButton(ui->btn_max,
                                Global::SystemButtonType::Maximize);

        connect(
            ui->btn_close, &QAbstractButton::clicked, this, &QWidget::close);
        connect(ui->btn_min,
                &QAbstractButton::clicked,
                this,
                &QWidget::showMinimized);
        connect(ui->btn_max,
                &QAbstractButton::clicked,
                this,
                [=]()
                {
                    if (isMaximized())
                        showNormal();
                    else
                        showMaximized();
                });
    }

    // SECTION - Setup menus
    {
        ui->bottom_left_view->setModel(_bottom_left_menu_model);
        ui->bottom_left_view->setVerticalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
        ui->bottom_left_view->setMaximumHeight(
            static_cast<int>(ITEM_HEIGHT)
            * static_cast<int>(BottomLeftMenuModel::ROW_COUNT));
    }

    // SECTION - The pipeline
    {
        setupDataViewLightStyle();

        std::shared_ptr<NodeDelegateModelRegistry> registry = ([]{
            auto ret = std::make_shared<NodeDelegateModelRegistry>();
            ret->registerModel<MyDataModel>();
            return ret;
        })();

        _dataFlowGraphModel = std::make_shared<DataFlowGraphModel>(registry);
        _vtkPipeLineScene = new VtkPipelineScene(*_dataFlowGraphModel);
        _vtkPipeLineView = new VtkPipelineView(_vtkPipeLineScene, this);
        ui->lay_right->addWidget(_vtkPipeLineView);
        setupFlatStyle(_vtkPipeLineView);
    }

    // SECTION - Setup style
    {
        for (const auto& btn : findChildren<QAbstractButton*>())
            setupFlatStyle(btn);

        for (const auto& view : findChildren<QAbstractItemView*>())
            setupFlatStyle(view);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    FramelessMainWindow::resizeEvent(event);
    if (isMaximized())
        ui->btn_max->setIcon(QIcon(":/style/icon/show_original_size.svg"));
    else
        ui->btn_max->setIcon(QIcon(":/style/icon/show_max_size.svg"));
}
