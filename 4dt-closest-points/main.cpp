#include <QtGui/QApplication>
#include "point.h"
#include "route.h"
#include "routereader.h"
#include "geometrichashing.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
