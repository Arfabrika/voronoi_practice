#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(true);
    /*mathmodule->GetIntersectionLines(*(new QLine(-100,-1,200,2)), *new QLine(1,1,2,1));
    mathmodule->GetIntersectionLines(*(new QLine(1,1,2,1)), *new QLine(1,2,3,2));*/
    /*bool tmp =
    mathmodule->isPointOnSegment(*(new QLine(-5,-5,10,10)),*(new point(0 ,1)));
    qDebug() << tmp;*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::generateColor()
{
    char hex_char[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E', 'F'};
    int color = 0;
    for (int i = 0; i < 6; i++)
        color = color * 16 + (hex_char[rand() % 16] - '0');
    return color;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));

    for (int i = 0; i < locuses.size(); i++)
    {
        painter.setBrush(QBrush(locuses[i]->getColor(), Qt::SolidPattern));
        painter.drawEllipse(locuses[i]->getPoint()->getX() -3,
                            locuses[i]->getPoint()->getY() -3, 6, 6);
    }
    painter.setBrush(QBrush(0xFFFFFF, Qt::SolidPattern));
    for (int i = 0; i < centralPerps.size(); i++)
        painter.drawLine(*centralPerps[i]);
    painter.end();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QRect wid = ui->field->geometry();
    if (e->button() == Qt::LeftButton
            && e->x() > wid.topLeft().x() + 3
            && e->y() > wid.topLeft().y() + 3
            && e->x() < wid.bottomRight().x() - 3
            && e->y() < wid.bottomRight().y() - 3)
    {
        ui->coords->setText(QString("%1:%2").arg(e->x()).arg(e->y()));
        int color = generateColor();

        point *pt = new point(e->x(),e->y());
        locus *loc = new locus(pt, color);
        makeCentralPerps(pt);
        locuses.push_back(loc);
        update();
    }
}

void MainWindow::makeCentralPerps(point* center)
{
    for (int i = 0; i < locuses.size(); i++)
    {
        QLine *l = new QLine(center->getX(), center->getY(),
                       locuses[i]->getPoint()->getX(),
                       locuses[i]->getPoint()->getY());
        centralPerps.push_back(l);
    }
}
