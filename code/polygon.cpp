#include "polygon.h"
#include "math.h"
#include "QVector"
#include "QPoint"

polygon::polygon()
{

}

polygon::polygon(QVector<QPoint*> v)
{
    vertices = v;
}

QVector<QPoint*> polygon::GetIntersection(QLine &l)
{
    math* m = new math;
    QVector<QPoint*> intersec;
    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        QLine *curLine = new QLine(*vertices[i], *vertices[j]);
        QPoint *inter = m->GetIntersectionSegments(l, *curLine);
        //if (intersec.indexOf(inter) == -1)//(!intersec.contains(inter))
        bool flag = true;
        for (int i = 0; i < intersec.size(); i++)
        {
            if (intersec[i]->x() == inter->x() && intersec[i]->y() == inter->y())
            {
                flag = false;
                break;
            }
        }
            if (flag && inter->x() != INT_MAX && inter->y() != INT_MAX/* && (intersec.contains(inter))*/)
                intersec.push_back(inter);
    }
    return intersec;
}
/*vector<Point2D> Polygon::GetIntersection(const Segment2D& segment) const
{
    vector<Point2D> intersect_points;
    for (size_t i = 0; i < this->Size(); ++i) {
        size_t j = (i + 1) % this->Size();
        Segment2D cur_side(vertices_[i], vertices_[j]);
        Point2D cur_intersection = segment.GetIntersection(cur_side);
        if (cur_intersection != kInfPoint2D) {
            intersect_points.push_back(cur_intersection);
        }
    }
    return intersect_points;
}*/
