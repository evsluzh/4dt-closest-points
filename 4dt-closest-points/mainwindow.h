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
    void on_pushButton_clicked();
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Route> routes;
};

