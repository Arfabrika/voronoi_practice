#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(true);

    QPointF *a = new QPointF(1,1),
            *b = new QPointF(3,5),
            *c = new QPointF(7,5),
            *d = new QPointF(7,1),
            *e = new QPointF(3,-1),
            *k = new QPointF(5, 7),
            *l = new QPointF(8,4),
            *m = new QPointF(5,4),
            *t = new QPointF(1,-1);
    QVector<QPointF*> vec, vec2;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    vec.push_back(e);
    vec2.push_back(k);
    vec2.push_back(l);
    vec2.push_back(m);
    polygon* p = new polygon(vec), *p2 = new polygon(vec2), *p3;
    /*QLineF *l1 = new QLineF(0,6,11,0);
    QVector<QPointF*> ans = p->GetIntersection(*l1);*/
    QVector<QPointF*> ans = p->GetIntersection(*p2);
    //bool qqq = p->isPointInPolygon(*t);
    //p3 = p->getIntersectPolygon(*p2);
    /*mathmodule->GetIntersectionLines(*(new QLineF(-100,-1,200,2)), *new QLineF(1,1,2,1));
    mathmodule->GetIntersectionLines(*(new QLineF(1,1,2,1)), *new QLineF(1,2,3,2));*/
    /*bool tmp =
    mathmodule->isPointOnSegment(*(new QLineF(-5,-5,10,10)),*(new QPointF(0 ,0)));
    qDebug() << tmp;*/
    /*QLineF *l1 = new QLineF(-1,-1,0,1), *l2 = new QLineF(4,0,0,4);
    QPointF *a = mathmodule->GetIntersectionSegments(*l1, *l2);
    a = mathmodule->GetIntersectionSegments(*new QLineF(-1,-1,2,5), *new QLineF(4,0,0,4));
    a = mathmodule->GetIntersectionSegments(*new QLineF(-1,-1,-1,6), *new QLineF(-2,6,0,4));
    a = mathmodule->GetIntersectionSegments(*new QLineF(-1,-1,-3,-1), *new QLineF(1,6,0,6));
    a = mathmodule->GetIntersectionSegments(*new QLineF(-100,-1,100,1), *new QLineF(4,0,0,4));
    a = nullptr;*/
    ans.clear();
    QVector<QPointF*> borderPts;
    borderPts.push_back(new QPointF(10,10));
    borderPts.push_back(new QPointF(10,500));
    borderPts.push_back(new QPointF(500,500));
    borderPts.push_back(new QPointF(500,10));
    border = new polygon(borderPts);
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
        QPointF *pt;// = new QPointF(100, 100);//new QPointF(e->x(),e->y());
        switch (cnt) {
        case 0:
            pt = new QPointF(100, 100);
            break;
        case 1:
            pt = new QPointF(300, 300);
            break;
        default:
            pt = new QPointF(e->x(),e->y());
            break;
        }
        QVector<QPointF*> points;
        for (int i = 0; i < locuses.size(); i++)
            points.push_back(locuses[i]->getPoint());
        points.push_back(pt);
        //points.push_back(new QPointF(100,100));
        //points.push_back(new QPointF(300,300));
        //locus *loc = createLocus(*pt, points);
        updateLocuses(points);
        makeCentralPerps(pt);
        //locuses.push_back(loc);
        cnt++;
        update();
    }
}

void MainWindow::makeCentralPerps(QPointF* center)
{
    for (int i = 0; i < locuses.size(); i++)
    {
        QLineF *l = new QLineF(center->x(), center->y(),
                       locuses[i]->getPoint()->x(),
                       locuses[i]->getPoint()->y());
        centralPerps.push_back(l);
    }
}

//Instead points -locuses array
locus* MainWindow::createLocus(QPointF &site, QVector<QPointF *> points)
{
    QVector<QLineF*> halfPlanes;
    for (int i = 0; i < /*locuses.size()*/ points.size(); i++)
    {
        QPointF* curPoint = points[i];//locuses[i]->getPoint();//points[i];//
        if (!(curPoint->x() == site.x() && curPoint->y() == site.y()))
        {
            QLineF* curSeg = new QLineF(site, *curPoint);
            QPointF* center = new QPointF((curSeg->x1() + curSeg->x2()) / 2,
                                          (curSeg->y1() + curSeg->y2()) / 2);
            float a = curSeg->y1() - curSeg->y2(),
                  b = curSeg->x2() - curSeg->x1();
            QPointF* normVec = new QPointF(center->x() + a, center->y() + b);
            QLineF* curHalfPlane = new QLineF(*center, *normVec);
            halfPlanes.push_back(curHalfPlane);
        }
    }
    int color = generateColor();
    polygon* p = border->getIntersectHalfPlanes(site, halfPlanes, *border);
    locus* curLocus = new locus(&site, p, color);
    return curLocus;
}

void MainWindow::updateLocuses(QVector<QPointF *> points)
{
    locuses.clear();
    for (int i = 0; i < points.size(); i++)
    {
        locus* curLocus = createLocus(*points[i], points);
        locuses.push_back(curLocus);
    }
}
