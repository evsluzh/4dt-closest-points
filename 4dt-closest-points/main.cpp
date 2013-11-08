#include <QtCore/QCoreApplication>
#include "Point.h"
#include "Route.h"
#include "RouterReader.h"
#include "GeometricHashing.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    return a.exec();
}
