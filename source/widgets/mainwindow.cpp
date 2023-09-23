#include "mainwindow.h"

#include <qabstractbutton.h>
#include <qabstractitemview.h>
#include <qframe.h>
#include <qlayoutitem.h>
#include <qlistview.h>
#include <qnamespace.h>
#include <qsizepolicy.h>

#include "constraint/item_in_view.hpp"
#include "ui_mainwindow.h"
#include "widgets/bottom_left_menu/bottom_left_menu_model.hpp"
#include "widgets/bottom_left_menu/bottom_left_menu_view.hpp"
#include "widgets/vtk_shapes/vtk_shapes_model.hpp"
#include "widgets/vtk_shapes/vtk_shapes_view.hpp"

MainWindow::MainWindow(QWidget* parent)
    : FramelessMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _bottom_left_menu_model(new BottomLeftMenuModel(this))
{
    ui->setupUi(this);

    // SECTION - Setup menus
    {
        ui->bottom_left_view->setModel(_bottom_left_menu_model);
        ui->bottom_left_view->setVerticalScrollBarPolicy(
            Qt::ScrollBarAlwaysOff);
        ui->bottom_left_view->setMaximumHeight(
            ITEM_HEIGHT * BottomLeftMenuModel::ROW_COUNT);
    }

    // SECTION - Setup style
    {
        for (const auto& btn : findChildren<QAbstractButton*>()) {
            btn->setProperty("flat", true);
        }
        for (const auto& btn : findChildren<QAbstractItemView*>()) {
            btn->setProperty("flat", true);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
