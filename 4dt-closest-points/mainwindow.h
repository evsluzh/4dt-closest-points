#pragma once

#include "route.h"
#include "edge.h"
#include "route.h"
#include "conflict.h"
#include "drawer.h"
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

    void on_actionSave_triggered();

    void on_actionGenerate_routes_triggered();

    void on_sliderT_valueChanged(int value);

    void on_sliderD_valueChanged(int value);

    void on_listWidget_currentRowChanged(int currentRow);

private:
    void find_conflicts();
    void draw();

    Ui::MainWindow *ui;
    std::vector<Route> m_routes;
    std::vector<Conflict> m_conflicts;
    Drawer m_drawer;
};
