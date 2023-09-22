#include <QApplication>
#include <QWidget>
#include <iostream>
#include <string>

#include <qapplication.h>
#include <qwidget.h>

auto main(int argc, char** argv) -> int
{
    QApplication app(argc, argv);

    QWidget w;
    w.show();
    return app.exec();
}
