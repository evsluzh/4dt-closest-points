#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "routereader.h"
#include "conflictpredictor.h"
#include "simplepredictor.h"
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

void MainWindow::draw_projection(boost::function<double (Point)> x, boost::function<double (Point)> y, QLabel* label)
{
    QRect rect(label->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));

    for (auto route_it = m_routes.begin(); route_it != m_routes.end(); ++route_it)
    {
        std::cout << "GO " << route_it->edge(0)->a()->x() << std::endl;
        for (size_t i = 0; i != route_it->size(); ++i)
        {
            boost::shared_ptr<Edge> edge = route_it->edge(i);
            painter.drawLine(x(*edge->a()), y(*edge->a()),
                             x(*edge->b()), y(*edge->b()));
        }
    }
    /*(painter.setPen(QPen(Qt::red));
    for (size_t i = 0; i < ts.size(); ++i)
    {
        while (ptr1 < route1.size() && route1.point(ptr1)->t() < ts[i].first)
        {
            ++ptr1;
        }
        while (ptr2 < route2.size() && route2.point(ptr2)->t() < ts[i].first)
        {
            ++ptr2;
        }
        while (ptr1 < route1.size() && route1.point(ptr1)->t() < ts[i].second)
        {
            painter.drawLine(route1.point(ptr1 - 1)->t(), route1.point(ptr1 - 1)->y(),
                             route1.point(ptr1)->t(), route1.point(ptr1)->y());
            ++ptr1;
        }

        while (ptr2 < route2.size() && route2.point(ptr2)->t() < ts[i].second)
        {
            painter.drawLine(route2.point(ptr2 - 1)->t(), route2.point(ptr2 - 1)->y(),
                             route2.point(ptr2)->t(), route2.point(ptr2)->y());
            ++ptr2;
        }
    }

    Point p1 = route1.get_position(t);
    Point p2 = route2.get_position(t);

    painter.drawEllipse(p1.t(), p1.y(), 5, 5);
    painter.drawEllipse(p2.t(), p2.y(), 5, 5);
    std::cout << "time = " << t << ' ' << p1.t() << ' ' << t << std::endl;*/
    painter.end();
    label->setPixmap(QPixmap::fromImage(sourceImage));
}

void MainWindow::draw_projections()
{
    double d = ui->spinD->value();
    double t = ui->spinT->value();
//    ConflictPredictor* predictor = new SimplePredictor(m_routes);
//    std::vector< std::pair<double, double> > conflicts = predictor->getConflict(0, 1, d);

    draw_projection(&Point::t, &Point::x, ui->proection_xt);
    draw_projection(&Point::t, &Point::y, ui->proection_yt);
    draw_projection(&Point::y, &Point::x, ui->proection_yx);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    RouteReader reader(fileName.toStdString().c_str());
    m_routes = reader.read();
    draw_projections();
}

void MainWindow::on_sliderT_valueChanged(int)
{
    draw_projections();
}

void MainWindow::on_sliderD_valueChanged(int)
{
    draw_projections();
}
