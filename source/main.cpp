#include <QApplication>
#include <QWidget>
#include <iostream>
#include <string>

#include <qapplication.h>
#include <qwidget.h>

#include "utils/helper_ui.h"
#include "widgets/mainwindow.h"

auto main(int argc, char** argv) -> int
{
    QApplication app(argc, argv);
    app.setStyleSheet(
        ([]
         { return HelperUi::readFileContent(":/style/qss/flatwhite.css"); })());
    MainWindow w;
    w.show();
    return app.exec();
}
