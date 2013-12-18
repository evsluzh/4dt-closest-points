#pragma once

#include "route.h"
#include "edge.h"
#include "route.h"
#include <vector>
#include <QtGui/QMainWindow>
#include <QtGui/QLabel>
#include <boost/function.hpp>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionGenerate_routes_triggered();

    void on_sliderT_valueChanged(int value);

    void on_sliderD_valueChanged(int value);

private:
    void draw_projections();
    void draw_projection(boost::function<double (Point)> x, boost::function<double (Point)> y,
                         QLabel* label, const std::vector< std::pair<double, double> >& conflicts, double t);

    std::pair<int, int> normalize(double x, double y, double minx, double maxx, double miny, double maxy, QLabel* label) const;

    Ui::MainWindow *ui;
    std::vector<Route> m_routes;
};
