#pragma once

#include <QtGui/QMainWindow>
#include <vector>
#include "Route.h"

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

private:
    void draw_proection1(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t);
    void draw_proection2(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t);
    void draw_proection(const Route& route1, const Route& route2, std::vector< std::pair<double, double> > ts, double t);
    void draw_routes(const std::vector<Route> routes);

    Ui::MainWindow *ui;
    std::vector<Route> routes;
};
