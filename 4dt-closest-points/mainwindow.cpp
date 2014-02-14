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
    std::cout << "Conflicts count: " << m_conflicts.size() << std::endl;
    ui->listWidget->clear();
    for (const Conflict& conflict : m_conflicts)
    {
        QString name = QString("Conflict between trajectories %1 and %2. Time: [%3, %4]")
                .arg(conflict.route1_index())
                .arg(conflict.route2_index())
                .arg(conflict.start_time())
                .arg(conflict.finish_time());
        ui->listWidget->addItem(name);
    }
}

void MainWindow::draw()
{
    double t = ui->spinT->value();
    int index = ui->listWidget->currentRow();
    std::vector<Route> routes;
    std::vector<Conflict> conflicts;
    if (index != -1)
    {
        Conflict conflict(0, 1, m_conflicts[index].start_time(), m_conflicts[index].finish_time());
        conflicts.push_back(conflict);
        size_t index1 = m_conflicts[index].route1_index();
        size_t index2 = m_conflicts[index].route2_index();
        routes.push_back(m_routes[index1]);
        routes.push_back(m_routes[index2]);
    }
    else
    {
        routes = m_routes;
    }
    m_drawer.draw(routes, t, conflicts);
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
        find_conflicts();
        draw();
    }
}

void MainWindow::on_actionGenerate_routes_triggered()
{
    boost::scoped_ptr<GenerateDialog> dialog(new GenerateDialog(this));
    if (dialog->exec() == QDialog::Accepted)
    {
        std::cout << "Task accepted" << std::endl;
        boost::scoped_ptr<RoutesGenerator> gen(new RoutesGenerator(dialog->based_points(),
                                                       dialog->routes_count(), dialog->route_points()));
        std::cout << "Generating..." << std::endl;
        m_routes = gen->generate();
        std::cout << "Finding for conflicts..." << std::endl;
        find_conflicts();
        std::cout << "Drawing" << std::endl;
        draw();
    }
}

void MainWindow::on_sliderT_valueChanged(int)
{
    draw();
}

void MainWindow::on_sliderD_valueChanged(int)
{
    find_conflicts();
    draw();
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    draw();
}
