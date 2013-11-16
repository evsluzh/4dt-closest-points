#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RouteReader.h"
#include "ConflictPredictor.h"
#include "SimplePredictor.h"
#include <QtGui/QPainter>
#include <QtGui/QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_proection(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{
    QRect    rect(ui->proection->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));
    for (size_t i = 1; i < route1.size(); ++i)
    {
        painter.drawLine(route1.point(i - 1).x(), route1.point(i - 1).y(),
                         route1.point(i).x(), route1.point(i).y());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.size(); ++i)
    {
        painter.drawLine(route2.point(i - 1).x(), route2.point(i - 1).y(),
                         route2.point(i).x(), route2.point(i).y());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].second)
        {
            painter.drawLine(route1.point(ptr1 - 1).x(), route1.point(ptr1 - 1).y(),
                             route1.point(ptr1).x(), route1.point(ptr1).y());
            ++ptr1;
        }

        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].second)
        {
            painter.drawLine(route2.point(ptr2 - 1).x(), route2.point(ptr2 - 1).y(),
                             route2.point(ptr2).x(), route2.point(ptr2).y());
            ++ptr2;
        }
    }

    Point p1 = route1.get_position(t);
    Point p2 = route2.get_position(t);
    std::cout << "Point = " <<  p1.x() << ' ' << p1.y() << std::endl;

    painter.drawEllipse(p1.x(), p1.y(), 5, 5);
    painter.drawEllipse(p2.x(), p2.y(), 5, 5);
    painter.end();

    ui->proection->setPixmap(QPixmap::fromImage(sourceImage));
}

void MainWindow::draw_proection1(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{
    QRect rect(ui->proection1->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));
    for (size_t i = 1; i < route1.size(); ++i)
    {
        painter.drawLine(route1.point(i - 1).t(), route1.point(i - 1).x(),
                         route1.point(i).t(), route1.point(i).x());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.size(); ++i)
    {
        painter.drawLine(route2.point(i - 1).t(), route2.point(i - 1).x(),
                         route2.point(i).t(), route2.point(i).x());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].second)
        {
            painter.drawLine(route1.point(ptr1 - 1).t(), route1.point(ptr1 - 1).x(),
                             route1.point(ptr1).t(), route1.point(ptr1).x());
            ++ptr1;
        }

        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].second)
        {
            painter.drawLine(route2.point(ptr2 - 1).t(), route2.point(ptr2 - 1).x(),
                             route2.point(ptr2).t(), route2.point(ptr2).x());
            ++ptr2;
        }
    }

    Point p1 = route1.get_position(t);
    Point p2 = route2.get_position(t);

    painter.drawEllipse(p1.t(), p1.x(), 5, 5);
    painter.drawEllipse(p2.t(), p2.x(), 5, 5);
    painter.end();

    ui->proection1->setPixmap(QPixmap::fromImage(sourceImage));
}

void MainWindow::draw_proection2(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{
    QRect    rect(ui->proection2->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));
    for (size_t i = 1; i < route1.size(); ++i)
    {
        painter.drawLine(route1.point(i - 1).t(), route1.point(i - 1).y(),
                         route1.point(i).t(), route1.point(i).y());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.size(); ++i)
    {
        painter.drawLine(route2.point(i - 1).t(), route2.point(i - 1).y(),
                         route2.point(i).t(), route2.point(i).y());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.size() && route1.point(ptr1).t() < ts[i].second)
        {
            painter.drawLine(route1.point(ptr1 - 1).t(), route1.point(ptr1 - 1).y(),
                             route1.point(ptr1).t(), route1.point(ptr1).y());
            ++ptr1;
        }

        while (ptr2 < route2.size() && route2.point(ptr2).t() < ts[i].second)
        {
            painter.drawLine(route2.point(ptr2 - 1).t(), route2.point(ptr2 - 1).y(),
                             route2.point(ptr2).t(), route2.point(ptr2).y());
            ++ptr2;
        }
    }

    Point p1 = route1.get_position(t);
    Point p2 = route2.get_position(t);

    painter.drawEllipse(p1.t(), p1.y(), 5, 5);
    painter.drawEllipse(p2.t(), p2.y(), 5, 5);
    std::cout << "time = " << t << ' ' << p1.t() << ' ' << t << std::endl;
    painter.end();

    ui->proection2->setPixmap(QPixmap::fromImage(sourceImage));
}

void MainWindow::draw_routes(const std::vector<Route> routes)
{
    double d = ui->spinD->value();
    double t = ui->spinT->value();
    ConflictPredictor* predictor = new SimplePredictor(routes);
    std::vector< std::pair<double, double> > conflicts = predictor->getConflict(0, 1, d);

    draw_proection1(routes[0], routes[1], conflicts, t);
    draw_proection2(routes[0], routes[1], conflicts, t);
    draw_proection(routes[0], routes[1], conflicts, t);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    RouteReader reader(fileName.toStdString().c_str());
    routes = reader.read();
    draw_routes(routes);
}

void MainWindow::on_sliderT_valueChanged(int)
{
    draw_routes(routes);
}

void MainWindow::on_sliderD_valueChanged(int)
{
    draw_routes(routes);
}
