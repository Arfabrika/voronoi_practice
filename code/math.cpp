#include "math.h"
#include <QtMath>

math::math()
{
    infNegPoint = new QPointF(-INT_MAX, -INT_MAX);
    infPoint = new QPointF(INT_MAX, INT_MAX);
}

//a < b
bool math::isSmaller(float a, float b)
{
    if ((a <= b + 1e-2) || (a <= b - 1e-2) || (a + 1e-2 <= b) ||  (a - 1e-2 <= b))
        return true;
    return false;
}

bool math::isBigger(float a, float b)
{
    if ((a >= b + 1e-2) || (a >= b - 1e-2) || (a + 1e-2 >= b) ||  (a - 1e-2 >= b))
        return true;
    return false;
}

bool math::isPointOnSegment(QLineF &l, QPointF p)
{
    float xmin = qMin(l.x1(), l.x2()),
        ymin = qMin(l.y1(), l.y2()),
        xmax = qMax(l.x1(), l.x2()),
        ymax = qMax(l.y1(), l.y2());
    if (isSmaller(xmin, p.x()) && isBigger(xmax, p.x()) &&
        isSmaller(ymin, p.y()) && isBigger(ymax, p.y()))
    {
        float a = l.y1() - l.y2(),
        b = l.x2() - l.x1(),
        c = l.x1() * l.y2() - l.x2() * l.y1();
        if (fabs(a * p.x() + b * p.y() + c) <= 1)
            return true;
    }
    return false;
}

QPointF* math::GetIntersectionLines(QLineF &l1, QLineF&l2)
{
    QPointF* intersect_point;
    float x1 = l1.x1(), x2 = l1.x2(), y1 = l1.y1(), y2 = l1.y2(),
        x3 = l2.x1(), x4 = l2.x2(), y3 = l2.y1(), y4 = l2.y2();
    float a1, a2, b1, b2, c1, c2;
    a1 = y1 - y2;
    b1 = x2 - x1;
    c1 = x1 * y2 - x2 * y1;
    a2 = y3 - y4;
    b2 = x4 - x3;
    c2 = x3 * y4 - x4 * y3;
    float det = a1 * b2 - a2 * b1;
    if (fabs(det) <= 1e-2)
    {
        (fabs(b1 * c2 - b2* c1) <= 1e-2)
        ?
            intersect_point = infNegPoint
        :
            intersect_point = infPoint;
    }
    else
    {

    float xinter = (b1 * c2 - b2 * c1) / det,
        yinter = (a2 * c1 - a1 * c2) / det;
    intersect_point = new QPointF(xinter, yinter);
    }
    return intersect_point;
}

QPointF* math::GetIntersectionLineAndSegment(QLineF &l, QLineF &seg)
{
    QPointF* inter = GetIntersectionLines(l, seg);
    if (inter->x() == infNegPoint->x() && inter->y() == infNegPoint->y())
        inter = new QPointF(seg.p2());
    else if ((!(inter->x() == infPoint->x() && inter->y() == infPoint->y())) &&
             !isPointOnSegment(seg, *inter))
        inter = infPoint;
    return inter;
}
