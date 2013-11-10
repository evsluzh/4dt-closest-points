#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RouteReader.h"
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

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));
    RouteReader reader(fileName.toStdString().c_str());
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
