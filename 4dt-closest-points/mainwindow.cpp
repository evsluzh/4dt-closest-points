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

void MainWindow::draw_proection1(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{

}

void MainWindow::draw_proection2(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{

}

void MainWindow::draw_proection(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t)
{

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


void MainWindow::on_pushButton_clicked()
{
    QRect    rect(ui->proection1->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 255, 0)));
    painter.drawLine(0,0,100,100);
    painter.end();

    ui->proection1->setPixmap(QPixmap::fromImage(sourceImage));

}
