#include "polygon.h"
#include "math.h"

math* m = new math;

polygon::polygon()
{

}

polygon::polygon(QVector<QPointF*> v)
{
    vertices = v;
}

int polygon::size()
{
    return vertices.size();
}

QPointF* polygon::getPointByIndex(int ind)
{
    return vertices[ind];
}

QVector<QPointF*> polygon::getVertices()
{
    return vertices;
}

// 0 - intersect line, 1  - intersect segments
QVector<QPointF*> polygon::GetIntersection(QLineF &l)
{
    QVector<QPointF*> intersec;
    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        QLineF *curLine = new QLineF(*vertices[i], *vertices[j]);
        QPointF *inter = m->GetIntersectionLineAndSegment(l, *curLine);
        bool flag = true;
        for (int i = 0; i < intersec.size(); i++)
        {
            if (intersec[i]->x() == inter->x() && intersec[i]->y() == inter->y())
            {
                flag = false;
                break;
            }
        }
        if (flag && isPointOnField(*inter))
            intersec.push_back(inter);
    }
    return intersec;
}

QVector<QPointF*> polygon::GetIntersectionRay(QLineF &ray)
{
    QVector<QPointF*> pts = GetIntersection(ray);
    for (int i = 0; i < pts.size(); i++)
    {
        if (pts[i]->x() < ray.x1() || pts[i]->y() < ray.y1())
            pts.removeAt(i);
    }
    return pts;
}

polygon* polygon::GetIntersection(QPointF &pt, QLineF &l)
{
    QVector<QPointF*> intersec;

    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        QLineF *curLine = new QLineF(*vertices[i], *vertices[j]);
        QPointF *inter = m->GetIntersectionLineAndSegment(l, *curLine);
        if (inter->x() < 510 && inter->y() < 510 && inter->x() > 0 &&
                inter->y() > 0)
            intersec.push_back(inter);
        float a, b, c, vx = vertices[i]->x(), vy = vertices[i]->y();
        a = l.y1() - l.y2();
        b = l.x2() - l.x1();
        c = l.x1() * l.y2() - l.x2() * l.y1();
        float funcp = a * pt.x() + b * pt.y() + c,
                funcv = a * vx + b * vy + c;
        if ((funcp <= (10e-6) && funcv <= (10e-6)) ||
                (funcp / fabs(funcp) == funcv / fabs(funcv)))
            intersec.push_back(vertices[i]);
    }
    polygon *res = new polygon(intersec);
    res->sortVertices();
    return res;
}

bool polygon::isPointInPolygon(QPointF &p)
{
    QLineF *ray = new QLineF(p.x(),p.y(), INT_MAX, INT_MAX);
    QVector<QPointF*> points = GetIntersectionRay(*ray);
    int ptsCnt = points.size();
    for(auto pt : points)
    {
        (!isPointOnField(*pt))
         ?
            ptsCnt++

         :
         ((p.x() == pt->x() && p.y() == pt->y() && ptsCnt % 2 == 0)
          ?
            ptsCnt++
          :
          0
          );
    }
    return ptsCnt % 2;
}

bool polygon::isPointOnField(QPointF &p)
{
    if (p.x() == INT_MAX  || p.x() == -INT_MAX ||
            p.y() == INT_MAX  || p.y() == -INT_MAX)
        return false;
    return true;
}


void polygon::sortVertices()
{
    // find center
    float xc = 0, yc = 0;
    int sz = vertices.size();
    for (int i = 0; i < sz; i++)
    {
        xc += vertices[i]->x();
        yc += vertices[i]->y();
    }
    xc /= sz;
    yc /= sz;

    // count angle
    QVector<float> angles;
    for (int i = 0; i < vertices.size(); i++)
    {
        float xp = vertices[i]->x() - xc,
              yp = vertices[i]->y() - yc,
              cosa = xp / sqrt(xp * xp + yp * yp),
              angle = acos(fabs(cosa));
        (yp < 0)
        ?
        (
            (xp < 0)
            ?
                angle += M_PI
            :
                angle = 2 * M_PI - angle
        )
        :
            ((xp < 0) ? angle = M_PI - angle : 0);
        angles.push_back(angle);
    }

    // sort by angle
    for (int i = 0; i < angles.size() - 1; i++)
    {
        for (int j = i + 1; j < angles.size(); j++)
        {
            if (angles[i] > angles[j])
            {
                QPointF *tmp = vertices[i];
                vertices[i] = vertices[j];
                vertices[j] = tmp;

                float t = angles[i];
                angles[i] = angles[j];
                angles[j] = t;
            }
        }
    }
}

polygon* polygon::getIntersectHalfPlanes(QPointF &curPoint, QVector<QLineF *> halfPerps, polygon &pl)
{
    polygon* res = &pl;
    for (int i = 0; i < halfPerps.size(); i++)
        res = res->GetIntersection(curPoint, *halfPerps[i]);
    return res;
}
