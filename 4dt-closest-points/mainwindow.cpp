#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "routereader.h"
#include "conflictpredictor.h"
#include "simplepredictor.h"
#include <QtGui/QPainter>
#include <QtGui/QFileDialog>
#include <boost/scoped_ptr.hpp>

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

void MainWindow::draw_projection(boost::function<double (Point)> x, boost::function<double (Point)> y, QLabel* label, const std::vector< std::pair<double, double> >& conflicts)
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
        size_t j = 0;
        bool is_conflict = false;
        for (size_t i = 0; i != route_it->size(); ++i)
        {
            boost::shared_ptr<Edge> edge = route_it->edge(i);
            if (is_conflict)
            {
                painter.setPen(QPen(Qt::red));
            }
            else
            {
                painter.setPen(QPen(Qt::black));
            }
            painter.drawLine(x(*edge->a()), y(*edge->a()),
                             x(*edge->b()), y(*edge->b()));
            if (!is_conflict)
            {
                while (j < conflicts.size() && conflicts[j].first < edge->a()->t())
                {
                    ++j;
                }
                if (j < conflicts.size() && edge->a()->t() <= conflicts[j].first && conflicts[j].first <= edge->b()->t())
                {
                    is_conflict = true;
                    painter.setPen(QPen(Qt::red));
                    double t = conflicts[j].first;
                    Point start = edge->point(t);
                    painter.drawLine(x(start), y(start),
                                     x(*edge->b()), y(*edge->b()));
                }
            }

            if (is_conflict)
            {
                if (edge->a()->t() <= conflicts[j].second && conflicts[j].second <= edge->b()->t())
                {
                    is_conflict = false;
                    painter.setPen(QPen(Qt::black));
                    double t = conflicts[j].second;
                    Point start = edge->point(t);
                    painter.drawLine(x(start), y(start),
                                     x(*edge->b()), y(*edge->b()));
                    ++j;
                }
            }
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
    if (!m_routes.size())
    {
        return;
    }
    double d = ui->spinD->value();
    double t = ui->spinT->value();
    boost::scoped_ptr<ConflictPredictor> predictor(new SimplePredictor(m_routes));
    std::vector< std::pair<double, double> > conflicts = predictor->getConflict(0, 1, d);
    std::cout << "SIZE = " << conflicts.size() << std::endl;

    draw_projection(&Point::t, &Point::x, ui->proection_xt, conflicts);
    draw_projection(&Point::t, &Point::y, ui->proection_yt, conflicts);
    draw_projection(&Point::y, &Point::x, ui->proection_yx, conflicts);
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
