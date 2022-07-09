#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(true);
    /*QVector<QPointF*> a, b, c , d, e, f;
    a.push_back((new QPointF(10,10)));
    a.push_back((new QPointF(310,10)));
    a.push_back((new QPointF(10,310)));
    b.push_back((new QPointF(10,10)));
    b.push_back((new QPointF(410,10)));
    b.push_back((new QPointF(10,410)));
    polygon* p1 = new polygon(a), *p2 = new polygon(b), *r;
    r = p1->getIntersectPolygon(*p2);

    e.push_back(new QPointF(10,10));
    e.push_back(new QPointF(10,100));
    e.push_back(new QPointF(100,100));
    e.push_back(new QPointF(100,10));
    f.push_back(new QPointF(20,20));
    f.push_back(new QPointF(20,90));
    f.push_back(new QPointF(90,90));
    f.push_back(new QPointF(90,20));
    p1 = new polygon(e), p2 = new polygon(f);
    int q = p2->isPolygonInPolygon(*p1);

    c.push_back(new QPointF(10,10));
    c.push_back(new QPointF(10,100));
    c.push_back(new QPointF(100,100));
    c.push_back(new QPointF(100,10));
    d.push_back(new QPointF(10,10));
    d.push_back(new QPointF(10,100));
    d.push_back(new QPointF(50,150));
    d.push_back(new QPointF(100,100));

    d.push_back(new QPointF(100,10));
    p1 = new polygon(c), p2 = new polygon(d);
    r = p1->getIntersectPolygon(*p2);*/
    QVector<QPointF*> borderPts;
    borderPts.push_back(new QPointF(11,11));
    borderPts.push_back(new QPointF(11,509));
    borderPts.push_back(new QPointF(509,509));
    borderPts.push_back(new QPointF(509,11));
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
    painter.setBrush(QBrush(0xFFFFFF, Qt::SolidPattern));
    for (int i = 0; i < locuses.size(); i++)
    {
        locuses[i]->drawLocus(&painter);
        painter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
        painter.drawEllipse(locuses[i]->getPoint()->x() -3,
                            locuses[i]->getPoint()->y() -3, 6, 6);
    }
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
        QPointF *pt = new QPointF(e->x(),e->y());
        /*switch (cnt) {
        case 0:
            pt = new QPointF(100, 100);
            break;
        case 1:

            pt = new QPointF(300, 300);
            break;
        case 2:
            pt = new QPointF(100, 400);
            break;
        case 3:
            pt = new QPointF(410, 110);
            break;
        default:
            pt = new QPointF(e->x(),e->y());
            break;
        }*/
        QVector<QPointF*> points;
        for (int i = 0; i < locuses.size(); i++)
            points.push_back(locuses[i]->getPoint());
        points.push_back(pt);
        updateLocuses(points);
        makeCentralPerps(pt);
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
locus* MainWindow::createLocus(QPointF &site, QVector<QPointF *> points, int oldColor)
{
    QVector<QLineF*> halfPlanes;
    for (int i = 0; i < points.size(); i++)
    {
        QPointF* curPoint = points[i];
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
    if (!oldColor)
        oldColor = generateColor();
    polygon* p = border->getIntersectHalfPlanes(site, halfPlanes, *border);
    locus* curLocus = new locus(&site, p, oldColor);
    return curLocus;
}

void MainWindow::updateLocuses(QVector<QPointF *> points)
{
    QVector<int> colors;
    for (auto l : locuses)
        colors.push_back(l->getColor());
    locuses.clear();
    for (int i = 0; i < points.size(); i++)
    {
        locus* curLocus = createLocus(*points[i], points, (i >= colors.size() ? 0 : colors[i]));
        locuses.push_back(curLocus);
    }
}
