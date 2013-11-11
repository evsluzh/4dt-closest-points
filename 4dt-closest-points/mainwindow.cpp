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
    for (size_t i = 1; i < route1.get_size(); ++i)
    {
        painter.drawLine(route1.get_point(i - 1).get_x(), route1.get_point(i - 1).get_y(),
                         route1.get_point(i).get_x(), route1.get_point(i).get_y());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.get_size(); ++i)
    {
        painter.drawLine(route2.get_point(i - 1).get_x(), route2.get_point(i - 1).get_y(),
                         route2.get_point(i).get_x(), route2.get_point(i).get_y());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].second)
        {
            painter.drawLine(route1.get_point(ptr1 - 1).get_x(), route1.get_point(ptr1 - 1).get_y(),
                             route1.get_point(ptr1).get_x(), route1.get_point(ptr1).get_y());
            ++ptr1;
        }

        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].second)
        {
            painter.drawLine(route2.get_point(ptr2 - 1).get_x(), route2.get_point(ptr2 - 1).get_y(),
                             route2.get_point(ptr2).get_x(), route2.get_point(ptr2).get_y());
            ++ptr2;
        }
    }

    Point p1 = route1.get_point(t);
    Point p2 = route2.get_point(t);

    painter.drawEllipse(p1.get_x(), p1.get_y(), 5, 5);
    painter.drawEllipse(p2.get_x(), p2.get_y(), 5, 5);
    painter.end();

    ui->proection->setPixmap(QPixmap::fromImage(sourceImage));
}

void MainWindow::draw_proection1(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{
    QRect    rect(ui->proection1->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));
    for (size_t i = 1; i < route1.get_size(); ++i)
    {
        painter.drawLine(route1.get_point(i - 1).get_t(), route1.get_point(i - 1).get_x(),
                         route1.get_point(i).get_t(), route1.get_point(i).get_x());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.get_size(); ++i)
    {
        painter.drawLine(route2.get_point(i - 1).get_t(), route2.get_point(i - 1).get_x(),
                         route2.get_point(i).get_t(), route2.get_point(i).get_x());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].second)
        {
            painter.drawLine(route1.get_point(ptr1 - 1).get_t(), route1.get_point(ptr1 - 1).get_x(),
                             route1.get_point(ptr1).get_t(), route1.get_point(ptr1).get_x());
            ++ptr1;
        }

        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].second)
        {
            painter.drawLine(route2.get_point(ptr2 - 1).get_t(), route2.get_point(ptr2 - 1).get_x(),
                             route2.get_point(ptr2).get_t(), route2.get_point(ptr2).get_x());
            ++ptr2;
        }
    }

    Point p1 = route1.get_point(t);
    Point p2 = route2.get_point(t);

    painter.drawEllipse(p1.get_t(), p1.get_x(), 5, 5);
    painter.drawEllipse(p2.get_t(), p2.get_x(), 5, 5);
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
    for (size_t i = 1; i < route1.get_size(); ++i)
    {
        painter.drawLine(route1.get_point(i - 1).get_t(), route1.get_point(i - 1).get_y(),
                         route1.get_point(i).get_t(), route1.get_point(i).get_y());
    }

    painter.setPen(QPen(Qt::gray));
    for (size_t i = 1; i < route2.get_size(); ++i)
    {
        painter.drawLine(route2.get_point(i - 1).get_t(), route2.get_point(i - 1).get_y(),
                         route2.get_point(i).get_t(), route2.get_point(i).get_y());
    }
    size_t ptr1 = 1, ptr2 = 1;
    painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.get_size() && route1.get_point(ptr1).get_t() < ts[i].second)
        {
            painter.drawLine(route1.get_point(ptr1 - 1).get_t(), route1.get_point(ptr1 - 1).get_y(),
                             route1.get_point(ptr1).get_t(), route1.get_point(ptr1).get_y());
            ++ptr1;
        }

        while (ptr2 < route2.get_size() && route2.get_point(ptr2).get_t() < ts[i].second)
        {
            painter.drawLine(route2.get_point(ptr2 - 1).get_t(), route2.get_point(ptr2 - 1).get_y(),
                             route2.get_point(ptr2).get_t(), route2.get_point(ptr2).get_y());
            ++ptr2;
        }
    }

    Point p1 = route1.get_point(t);
    Point p2 = route2.get_point(t);

    painter.drawEllipse(p1.get_t(), p1.get_y(), 5, 5);
    painter.drawEllipse(p2.get_t(), p2.get_y(), 5, 5);
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
