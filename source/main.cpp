#include <QApplication>
#include <QWidget>
#include <iostream>
#include <string>

#include <QVTKRenderWidget.h>
#include <qapplication.h>
#include <qwidget.h>

#include <QtGui/QSurfaceFormat>

#include "utils/helper_ui.h"
#include "widgets/mainwindow.h"

auto main(int argc, char** argv) -> int
{
    // set surface format before application initialization
    QSurfaceFormat::setDefaultFormat(QVTKRenderWidget::defaultFormat());
    QApplication app(argc, argv);
    app.setStyleSheet(
        ([]
         { return HelperUi::readFileContent(":/style/qss/flatwhite.css"); })());
    MainWindow w;
    w.showMaximized();
    return app.exec();
}
