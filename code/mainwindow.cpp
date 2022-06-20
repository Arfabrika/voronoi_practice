#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->field->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    for (int i = 0; i < points.size(); i++)
        painter.drawEllipse(points[i].first, points[i].second, 25, 25);
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        ui->coords->setText(QString("%1:%2").arg(e->x()).arg(e->y()));//mouseMoveEvent(e);
        points.push_back(QPair<int, int>(e->x(),e->y()));
        update();
    }
}
