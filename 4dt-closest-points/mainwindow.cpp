#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "routereader.h"
#include "conflictpredictor.h"
#include "simplepredictor.h"
#include "geometrichashing.h"
#include "generatedialog.h"
#include "routesgenerator.h"
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

std::pair<int, int> MainWindow::normalize(double x, double y, double minx, double maxx, double miny, double maxy, QLabel* label) const
{
    x -= minx;
    y -= miny;
    maxx -= minx;
    maxy -= miny;
    return std::make_pair(label->width() * x / maxx, label->height() * y / maxy);
}

void MainWindow::draw_projection(boost::function<double (Point)> x, boost::function<double (Point)> y, QLabel* label, const std::vector< std::pair<double, double> >& conflicts, double t)
{
    QRect rect(label->contentsRect());

    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::white);
    QPainter painter;
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black));

    double minx = 1.0e99, maxx = -1.0e99;
    double miny = 1.0e99, maxy = -1.0e99;
    double mint = 1.0e99, maxt = -1.0e99;

    for (auto route_it = m_routes.begin(); route_it != m_routes.end(); ++route_it)
    {
        for (size_t i = 0; i <= route_it->size(); ++i)
        {
            minx = std::min(minx, x(*route_it->point(i)));
            maxx = std::max(maxx, x(*route_it->point(i)));

            miny = std::min(miny, y(*route_it->point(i)));
            maxy = std::max(maxy, y(*route_it->point(i)));

            mint = std::min(mint, route_it->point(i)->t());
            maxt = std::max(maxt, route_it->point(i)->t());
        }
    }
    double diffx = maxx - minx;
    double diffy = maxy - miny;
    double difft = maxt - mint;

    minx -= 0.1 * diffx;
    maxx += 0.1 * diffx;

    miny -= 0.1 * diffy;
    maxy += 0.1 * diffy;

    mint -= 0.1 * difft;
    maxt += 0.1 * difft;

    std::cout << "(" << minx << ", " << miny << ") (" << maxx << ", " << maxy << ")" << std::endl;

    for (auto route_it = m_routes.begin(); route_it != m_routes.end(); ++route_it)
    {
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
            std::pair<int, int> pa = normalize(x(*edge->a()), y(*edge->a()), minx, maxx, miny, maxy, label);
            std::pair<int, int> pb = normalize(x(*edge->b()), y(*edge->b()), minx, maxx, miny, maxy, label);
            painter.drawLine(pa.first, pa.second,
                             pb.first, pb.second);
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
                    Point start;
                    if (edge->get_point(t, start))
                    {
                        std::pair<int, int> pa = normalize(x(start), y(start), minx, maxx, miny, maxy, label);
                        std::pair<int, int> pb = normalize(x(*edge->b()), y(*edge->b()), minx, maxx, miny, maxy, label);
                        painter.drawLine(pa.first, pa.second,
                                         pb.first, pb.second);
                    }
                }
            }

            if (is_conflict)
            {
                if (edge->a()->t() <= conflicts[j].second && conflicts[j].second <= edge->b()->t())
                {
                    is_conflict = false;
                    painter.setPen(QPen(Qt::black));
                    double t = conflicts[j].second;
                    Point start;
                    if (edge->get_point(t, start))
                    {
                        std::pair<int, int> pa = normalize(x(start), y(start), minx, maxx, miny, maxy, label);
                        std::pair<int, int> pb = normalize(x(*edge->b()), y(*edge->b()), minx, maxx, miny, maxy, label);
                        painter.drawLine(pa.first, pa.second,
                                         pb.first, pb.second);
                    }
                    ++j;
                }
            }
        }
        Point p;
        double time = mint + (maxt - mint) * t * 0.01;
        if (route_it->get_position(time, p))
        {
            painter.setPen(QPen(Qt::red));
            std::pair<int, int> pt = normalize(x(p), y(p), minx, maxx, miny, maxy, label);
            painter.drawEllipse(pt.first, pt.second, 5, 5);
        }
    }
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
    std::cout << "PRECALC" << std::endl;
    boost::scoped_ptr<ConflictPredictor> predictor(new GeometricHashing(m_routes));
    std::cout << "OK" << std::endl;
//    boost::scoped_ptr<ConflictPredictor> predictor(new SimplePredictor(m_routes));
    for (size_t i = 0; i != m_routes.size(); ++i)
    {
        for (size_t j = i + 1; j != m_routes.size(); ++j)
        {
            predictor->getConflict(i, j, d);
        }
    }
    std::vector< std::pair<double, double> > conflicts = predictor->getConflict(0, 1, d);
    std::cout << "SIZE = " << conflicts.size() << std::endl;
    for (size_t i = 0; i < conflicts.size(); ++i)
    {
        std::cout << "(" << conflicts[i].first << ", " << conflicts[i].second << ")" << std::endl;
    }

    draw_projection(&Point::t, &Point::x, ui->proection_xt, conflicts, t);
    draw_projection(&Point::t, &Point::y, ui->proection_yt, conflicts, t);
    draw_projection(&Point::x, &Point::y, ui->proection_yx, conflicts, t);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    if (fileName.size() > 0)
    {
        RouteReader reader(fileName.toStdString().c_str());
        m_routes = reader.read();
        draw_projections();
    }
}

void MainWindow::on_actionGenerate_routes_triggered()
{
    GenerateDialog* dialog = new GenerateDialog(this);
//    dialog->show();
    if (dialog->exec() == QDialog::Accepted)
    {
        boost::scoped_ptr<RoutesGenerator> gen(new RoutesGenerator(dialog->based_points(), dialog->routes_count(), dialog->route_points()));
        m_routes = gen->generate();
        draw_projections();
    }
    delete dialog;
}

void MainWindow::on_sliderT_valueChanged(int)
{
    draw_projections();
}

void MainWindow::on_sliderD_valueChanged(int)
{
    draw_projections();
}
