#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "routereader.h"
#include "routewriter.h"
#include "conflictpredictor.h"
#include "simplepredictor.h"
#include "geometrichashing.h"
#include "generatedialog.h"
#include "routesgenerator.h"
#include <QtGui/QPainter>
#include <QtGui/QFileDialog>
#include <boost/scoped_ptr.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_drawer.add_graph(Drawer::Graph(&Point::t, &Point::x, ui->proection_xt));
    m_drawer.add_graph(Drawer::Graph(&Point::t, &Point::y, ui->proection_yt));
    m_drawer.add_graph(Drawer::Graph(&Point::x, &Point::y, ui->proection_yx));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::find_conflicts()
{
    double threshold = ui->spinD->value();
    boost::scoped_ptr<ConflictPredictor> predictor(new GeometricHashing(m_routes));
    m_conflicts = predictor->getConflicts(threshold);
}

void MainWindow::draw()
{
    double t = ui->spinT->value();
    m_drawer.draw(m_routes, t, std::vector<Conflict>());
//    m_drawer.draw_routes_indicators(m_routes, t);
//    m_drawer.draw_conflict();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"));
    if (fileName.size() > 0)
    {
        RouteWriter writer(fileName.toStdString().c_str());
        writer.write(m_routes);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("Files (*.*)"));
    if (fileName.size() > 0)
    {
        RouteReader reader(fileName.toStdString().c_str());
        m_routes = reader.read();
//        draw_projections();
        draw();
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
//        draw_projections();
        draw();
    }
    delete dialog;
}

void MainWindow::on_sliderT_valueChanged(int)
{
    draw();
}

void MainWindow::on_sliderD_valueChanged(int)
{
    draw();
}
