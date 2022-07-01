#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(true);

    QPoint *a = new QPoint(-2, -2),
            *b = new QPoint(-2, 2),
            *c = new QPoint(2, 2),
            *d = new QPoint(2, -2);
    QVector<QPoint*> vec;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    polygon* p = new polygon(vec);
    QLine *l1 = new QLine(-3,-3,3,3);
    QVector<QPoint*> ans = p->GetIntersection(*l1);

    /*mathmodule->GetIntersectionLines(*(new QLine(-100,-1,200,2)), *new QLine(1,1,2,1));
    mathmodule->GetIntersectionLines(*(new QLine(1,1,2,1)), *new QLine(1,2,3,2));*/
    /*bool tmp =
    mathmodule->isPointOnSegment(*(new QLine(-5,-5,10,10)),*(new QPoint(0 ,0)));
    qDebug() << tmp;*/
    /*QLine *l1 = new QLine(-1,-1,0,1), *l2 = new QLine(4,0,0,4);
    QPoint *a = mathmodule->GetIntersectionSegments(*l1, *l2);
    a = mathmodule->GetIntersectionSegments(*new QLine(-1,-1,2,5), *new QLine(4,0,0,4));
    a = mathmodule->GetIntersectionSegments(*new QLine(-1,-1,-1,6), *new QLine(-2,6,0,4));
    a = mathmodule->GetIntersectionSegments(*new QLine(-1,-1,-3,-1), *new QLine(1,6,0,6));
    a = mathmodule->GetIntersectionSegments(*new QLine(-100,-1,100,1), *new QLine(4,0,0,4));
    a = nullptr;*/
    ans.clear();
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
        painter.drawEllipse(locuses[i]->getPoint()->x() -3,
                            locuses[i]->getPoint()->y() -3, 6, 6);
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

        QPoint *pt = new QPoint(e->x(),e->y());
        locus *loc = new locus(pt, color);
        makeCentralPerps(pt);
        locuses.push_back(loc);
        update();
    }
}

void MainWindow::makeCentralPerps(QPoint* center)
{
    for (int i = 0; i < locuses.size(); i++)
    {
        QLine *l = new QLine(center->x(), center->y(),
                       locuses[i]->getPoint()->x(),
                       locuses[i]->getPoint()->y());
        centralPerps.push_back(l);
    }
}
