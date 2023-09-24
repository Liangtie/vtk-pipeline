#include <QFileDialog>
#include <QRegularExpression>
#include <memory>

#include "mainwindow.h"

#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <qabstractbutton.h>
#include <qabstractitemmodel.h>
#include <qabstractitemview.h>
#include <qapplication.h>
#include <qframe.h>
#include <qicon.h>
#include <qlayoutitem.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qsizepolicy.h>
#include <qsortfilterproxymodel.h>
#include <qwidget.h>

#include "constraint/item_in_view.hpp"
#include "ui_mainwindow.h"
#include "vtk_output/gltf/vtkGLTFImporterDelegate.hpp"
#include "vtk_output/image/vtkImageViewerDelegate.hpp"
#include "vtk_pipeline/data_view_light_style.hpp"
#include "vtk_pipeline/vtk_pipeline_scene.hpp"
#include "vtk_pipeline/vtk_pipeline_view.hpp"
#include "vtk_process/vtkImageResizeDelegate.hpp"
#include "vtk_shapes/vtk_shape_category.hpp"
#include "vtk_shapes/vtk_shapes_model.hpp"
#include "vtk_source/decimal/NumberSourceDataModel.hpp"
#include "vtk_source/file_path/vtkFilePathSelector.hpp"
#include "vtk_source/jpg/vtkJPGReaderDelegate.hpp"
#include "vtk_source/png/vtkPNGReaderDelegate.hpp"
#include "widgets/bottom_left_menu/bottom_left_menu_model.hpp"
#include "widgets/bottom_left_menu/bottom_left_menu_view.hpp"
#include "widgets/mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : FramelessMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _bottom_left_menu_model(new BottomLeftMenuModel(this))
{
    ui->setupUi(this);

    // SECTION - Frameless
    {
        using namespace wangwenx190::FramelessHelper;
        auto helper = FRAMELESSHELPER_PREPEND_NAMESPACE(
            FramelessWidgetsHelper)::get(this);
        // helper->setTitleBarWidget(ui->menu_top);

        helper->setSystemButton(ui->btn_close, Global::SystemButtonType::Close);
        helper->setSystemButton(ui->btn_min,
                                Global::SystemButtonType::Minimize);
        helper->setSystemButton(ui->btn_max,
                                Global::SystemButtonType::Maximize);
        helper->setSystemButton(ui->btn_open, Global::SystemButtonType::Help);
        helper->setSystemButton(ui->btn_save,
                                Global::SystemButtonType::WindowIcon);

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
        connect(qApp,
                &QApplication::applicationStateChanged,
                this,
                &MainWindow::onWindowsSizeChanged);
    }

    // SECTION - Setup menus
    {
        ui->bottom_left_view->setModel(_bottom_left_menu_model);
        ui->bottom_left_view->setVerticalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
        ui->bottom_left_view->setProperty("menu", true);
        ui->bottom_left_view->setMaximumHeight(
            static_cast<int>(ITEM_HEIGHT)
            * static_cast<int>(BottomLeftMenuModel::ROW_COUNT));
    }

    // SECTION - The pipeline
    {
        std::vector<std::shared_ptr<VtkBaseShape>> shapes;
        shapes.push_back(std::make_shared<VtkShapeCategory>(
            "Dataset",
            QString {},
            QIcon(":/style/icon/input.png"),
            std::vector<std::shared_ptr<VtkBaseShape>> {
                std::make_shared<NumberSourceDataModel>(),
                std::make_shared<vtkFilePathSelector>(),
                std::make_shared<vtkJPGReaderDelegate>(),
                std::make_shared<vtkPNGReaderDelegate>(),

            }));

        shapes.push_back(std::make_shared<VtkShapeCategory>(
            "Mapper",
            QString {},
            QIcon(":/style/icon/mapper.png"),
            std::vector<std::shared_ptr<VtkBaseShape>> {}));

        shapes.push_back(std::make_shared<VtkShapeCategory>(
            "Fitter",
            QString {},
            QIcon(":/style/icon/filter.png"),
            std::vector<std::shared_ptr<VtkBaseShape>> {}));

        shapes.push_back(std::make_shared<VtkShapeCategory>(
            "Process",
            QString {},
            QIcon(":/style/icon/process.png"),
            std::vector<std::shared_ptr<VtkBaseShape>> {
                std::make_shared<vtkImageResizeDelegate>(),

            }));

        shapes.push_back(std::make_shared<VtkShapeCategory>(
            "Output",
            QString {},
            QIcon(":/style/icon/output.png"),
            std::vector<std::shared_ptr<VtkBaseShape>> {
                std::make_shared<vtkImageViewerDelegate>(),
                std::make_shared<vtkGLTFImporterDelegate>(),
            }));

        _vtk_shapes_model =
            new VtkShapeModel(std::move(shapes), ui->vtk_shapes_view);

        // SECTION -The filter
        {
            const auto proxy = new QSortFilterProxyModel(this);
            proxy->setSourceModel(_vtk_shapes_model);
            proxy->setRecursiveFilteringEnabled(true);
            ui->vtk_shapes_view->setModel(proxy);
            ui->vtk_shapes_view->setProperty("highlight", true);
            ui->vtk_shapes_view->setProperty("menu", true);

            connect(ui->searchWidget,
                    &QLineEdit::textChanged,
                    this,
                    [=](const QString& fitter)
                    {
                        QRegularExpression regExp(
                            fitter,
                            QRegularExpression::PatternOption::
                                CaseInsensitiveOption);
                        proxy->setFilterRegularExpression(regExp);
                        if (fitter.size() != 0) {
                            ui->vtk_shapes_view->expandAll();
                        } else {
                            ui->vtk_shapes_view->collapseAll();
                        }
                    });
        }
    }

    // SECTION - The vtk pipeline view and scene
    {
        setupDataViewLightStyle();

        std::shared_ptr<NodeDelegateModelRegistry> registry = ([]{
            auto ret = std::make_shared<NodeDelegateModelRegistry>();
            ret->registerModel<NumberSourceDataModel>("Dataset");
            ret->registerModel<vtkFilePathSelector>("Dataset");
            ret->registerModel<vtkJPGReaderDelegate>("Dataset");
            ret->registerModel<vtkPNGReaderDelegate>("Dataset");

            ret->registerModel<vtkImageResizeDelegate>("Process");

            ret->registerModel<vtkImageViewerDelegate>("Output");
            ret->registerModel<vtkGLTFImporterDelegate>("Output");

            return ret;
        })();

        _dataFlowGraphModel = std::make_shared<DataFlowGraphModel>(registry);
        _vtkPipeLineScene = new VtkPipelineScene(*_dataFlowGraphModel);
        _vtkPipeLineView = new VtkPipelineView(_vtkPipeLineScene, this);
        ui->lay_right->addWidget(_vtkPipeLineView);
    }

    // SECTION - Setup style
    {
        static const auto setupFlatStyle = [](QObject* obj)
        { obj->setProperty("flat", true); };
        for (const auto& btn : findChildren<QAbstractButton*>())
            setupFlatStyle(btn);

        for (const auto& view : findChildren<QAbstractItemView*>())
            setupFlatStyle(view);
        setupFlatStyle(_vtkPipeLineView);
    }
    connect(ui->btn_open,
            &QAbstractButton::clicked,
            _vtkPipeLineScene,
            &VtkPipelineScene::load);
    connect(ui->btn_save,
            &QAbstractButton::clicked,
            _vtkPipeLineScene,
            &VtkPipelineScene::save);
    connect(ui->bottom_left_view,
            &QAbstractItemView::clicked,
            [](QModelIndex const& idx)
            {
                switch (idx.row()) {
                    case BottomLeftMenuModel::ROWS::ABOUT:
                        QApplication::aboutQt();
                        break;
                    case BottomLeftMenuModel::ROWS::SETTINGS:
                        break;
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    FramelessMainWindow::resizeEvent(event);
    onWindowsSizeChanged();
}

void MainWindow::onWindowsSizeChanged()
{
    static const QIcon icon_original(":/style/icon/show_original_size.png");
    static const QIcon icon_max(":/style/icon/show_max_size.png");

    if (isMaximized())
        ui->btn_max->setIcon(icon_original);
    else
        ui->btn_max->setIcon(icon_max);
}
