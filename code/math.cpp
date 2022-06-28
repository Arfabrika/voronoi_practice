#include "math.h"
#include <QDebug>
#include <QtMath>

math::math()
{

}

bool math::isPointOnSegment(QLine &l, point &p)
{
    int xmin = qMin(l.x1(), l.x2()),
        ymin = qMin(l.y1(), l.y2()),
        xmax = qMax(l.x1(), l.x2()),
        ymax = qMax(l.y1(), l.y2());
    if (xmin <= p.getX() && xmax >= p.getX()&&
        ymin <= p.getY() && ymax >= p.getY())
    {
        int a = l.y1() - l.y2(),
        b = l.x2() - l.x1(),
        c = l.x1() * l.y2() - l.x2() * l.y1();
        if (a * p.getX() + b * p.getY() + c == 0)
            return true;
    }
    return false;
}

point* math::GetIntersectionLines(QLine &l1, QLine&l2)
{
    l1 = l2;
    point* intersect_point;
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
            intersect_point = new point(-INT_MAX, -INT_MAX);
        else
            intersect_point = new point(INT_MAX, INT_MAX);
    }
    else
    {

    int xinter = (b1 * c2 - b2 * c1) / det,
        yinter = (a2 * c1 - a1 * c2) / det;
    intersect_point = new point(xinter, yinter);
    }
    qDebug() << intersect_point->getX() << intersect_point->getY();
    return intersect_point;
}

//first = this
point* math::GetIntersectionSegments(QLine &l1, QLine&l2)
{
     point* intersect_point = GetIntersectionLines(l1, l2);
     if (intersect_point == new point(-INT_MAX, -INT_MAX))
     {
         intersect_point = intersect_point->qPointToPoint(l1.p2());
         if (isPointOnSegment(l1, intersect_point->qPointToPoint(l1.p2())))
     }
     return intersect_point;
}
/*Point2D Segment2D::GetIntersection(const Segment2D& second_seg) const
{
    Line2D first_line(*this);
    Line2D second_line(second_seg);
    Point2D intersect_point = first_line.GetIntersection(second_line);
    if (intersect_point == kNegInfPoint2D) {
        if (this->Contains(second_seg.b)) {
            intersect_point = second_seg.b;
        } else if (this->Contains(second_seg.a)) {
            intersect_point = second_seg.a;
        } else if (second_seg.Contains(this->b)) {
            intersect_point = this->b;
        } else if (second_seg.Contains(this->a)) {
            intersect_point = this->a;
        } else {
            intersect_point = kInfPoint2D;
        }
    } else if (!(this->Contains(intersect_point) && second_seg.Contains(intersect_point))) {
            intersect_point = kInfPoint2D;
    }
    return intersect_point;
}*/
