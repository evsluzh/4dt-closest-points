#include <QtGui/QApplication>
#include "Point.h"
#include "Route.h"
#include "RouteReader.h"
#include "GeometricHashing.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
