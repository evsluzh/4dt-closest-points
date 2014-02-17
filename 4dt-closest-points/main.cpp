#include <QtGui/QApplication>
#include "core/point.h"
#include "core/route.h"
#include "routereader.h"
#include "core/geometrichashing.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
