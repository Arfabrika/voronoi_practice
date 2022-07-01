#include "math.h"
#include <QDebug>
#include <QtMath>

math::math()
{

}

bool math::isPointOnSegment(QLine &l, QPoint p)
{
    int xmin = qMin(l.x1(), l.x2()),
        ymin = qMin(l.y1(), l.y2()),
        xmax = qMax(l.x1(), l.x2()),
        ymax = qMax(l.y1(), l.y2());
    if (xmin <= p.x() && xmax >= p.x()&&
        ymin <= p.y() && ymax >= p.y())
    {
        int a = l.y1() - l.y2(),
        b = l.x2() - l.x1(),
        c = l.x1() * l.y2() - l.x2() * l.y1();
        if (a * p.x() + b * p.y() + c == 0)
            return true;
    }
    return false;
}

QPoint* math::GetIntersectionLines(QLine &l1, QLine&l2)
{
    QPoint* intersect_point;
    int x1 = l1.x1(), x2 = l1.x2(), y1 = l1.y1(), y2 = l1.y2(),
        x3 = l2.x1(), x4 = l2.x2(), y3 = l2.y1(), y4 = l2.y2();
    int a1, a2, b1, b2, c1, c2;
    a1 = y1 - y2;
    b1 = x2 - x1;
    c1 = x1 * y2 - x2 * y1;
    a2 = y3 - y4;
    b2 = x4 - x3;
    c2 = x3 * y4 - x4 * y3;
    int det = a1 * b2 - a2 * b1;
    if (abs(det) <= 1e-6)
    {
        if (abs(b1 * c2 - b2* c1) == 0)
            intersect_point = new QPoint(-INT_MAX, -INT_MAX);
        else
            intersect_point = new QPoint(INT_MAX, INT_MAX);
    }
    else
    {

    int xinter = (b1 * c2 - b2 * c1) / det,
        yinter = (a2 * c1 - a1 * c2) / det;
    intersect_point = new QPoint(xinter, yinter);
    }
    qDebug() << intersect_point->x() << intersect_point->y();
    return intersect_point;
}

QPoint* math::GetIntersectionSegments(QLine &l1, QLine&l2)
{
     QPoint* intersect_point  = GetIntersectionLines(l1, l2),
             *infPoint = new QPoint(-INT_MAX, -INT_MAX);

     if (intersect_point->x() == infPoint->x() && intersect_point->y() == infPoint->y())
     {
         if (isPointOnSegment(l1, l2.p2()))
            *intersect_point = l2.p2();
         else if (isPointOnSegment(l1, l2.p1()))
             *intersect_point = l2.p1();
         else if (isPointOnSegment(l2, l1.p2()))
             *intersect_point = l1.p2();
         else if (isPointOnSegment(l2, l1.p1()))
             *intersect_point = l1.p1();
         else
             intersect_point = new QPoint(INT_MAX, INT_MAX);
     }
     else if (!(isPointOnSegment(l1, *intersect_point) &&
              isPointOnSegment(l2, *intersect_point)))
         intersect_point = new QPoint(INT_MAX, INT_MAX);
     return intersect_point;
}

