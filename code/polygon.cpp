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

QVector<QPointF*> polygon::GetIntersection(QLineF &l)
{
    QVector<QPointF*> intersec;
    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        QLineF *curLine = new QLineF(*vertices[i], *vertices[j]);
        QPointF *inter = m->GetIntersectionLines(l, *curLine);//m->GetIntersectionSegments(l, *curLine);
        bool flag = true;
        for (int i = 0; i < intersec.size(); i++)
        {
            if (intersec[i]->x() == inter->x() && intersec[i]->y() == inter->y())
            {
                flag = false;
                break;
            }
        }
        if (flag || (inter->x() != INT_MAX && inter->y() != INT_MAX))
            intersec.push_back(inter);
    }
    return intersec;
}

QVector<QPointF*> polygon::GetIntersection(polygon &p)
{
    QVector<QPointF*> intersec, verts = p.getVertices();
    for (int i = 0; i < vertices.size(); i++)
    {
        int ind1 = (i + 1) % vertices.size();
        QLineF *curLine = new QLineF(*vertices[i], *vertices[ind1]);
        QVector<QPointF*> curInter = p.GetIntersection(*curLine);
        while(curInter.size() > 0)
        {
           QPointF* val = curInter.first();
           bool flag = true;
           for (int q = 0; q < intersec.size(); q++)
           {
               if (intersec[q]->x() == val->x() && intersec[q]->y() == val->y())
               {
                   flag = false;
                   break;
               }
           }
           if (flag)
              intersec.push_back(val);
           curInter.pop_front();
        }
    }
    return intersec;
}

polygon* polygon::GetIntersection(QPointF &pt, QLineF &l)
{
    QVector<QPointF*> intersec;

    for (int i = 0; i < vertices.size(); i++)
    {
        int j = (i + 1) % vertices.size();

        QLineF *curLine = new QLineF(*vertices[i], *vertices[j]);
        QPointF *inter = m->GetIntersectionLineAndSegment(l, *curLine);
        if (inter->x() != INT_MAX && inter->y() != INT_MAX && inter->x() > 0 &&
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
    QLineF *ray = new QLineF(0,0,p.x(),p.y());
    QVector<QPointF*> points = GetIntersection(*ray);
    return points.size() % 2;
}

polygon* polygon::getIntersectPolygon(polygon &p)
{
    QVector<QPointF*> interPoints = GetIntersection(p);
    for (int i = 0; i < p.size(); i++)
    {
        QPointF *curPoint = p.getPointByIndex(i);
        if (isPointInPolygon(*curPoint))
        {
            bool flag = true;
            for (int j = 0; j < interPoints.size(); j++)
            {
                if (vertices[j]->x() == curPoint->x() && vertices[j]->y() == curPoint->y())
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                interPoints.push_back(curPoint);
        }
    }
    polygon *res = new polygon(interPoints);
    res->sortVertices();
    return res;
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
        if (yp < 0)
        {
            if (xp < 0)
                angle += M_PI;
            else
                angle = 2 * M_PI - angle;
        }
        else
            if (xp < 0)
                angle = M_PI - angle;
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
    if (halfPerps.size() == 1)
    {
        polygon* res = pl.GetIntersection(curPoint, *halfPerps[0]);//new polygon(pl.GetIntersection(*halfPerps[0]));
        //res->sortVertices();
        return res;
    }
    else if (halfPerps.size() == 0)
    {
        polygon* res = &pl;
        return res;
    }
    else
    {
        int mid = halfPerps.size() / 2;
        QVector<QLineF *> fst(halfPerps.begin(), halfPerps.begin() + mid),
                          scd(halfPerps.begin() + mid , halfPerps.end());
        polygon* fstp(getIntersectHalfPlanes(curPoint, fst, pl)),
               * secp(getIntersectHalfPlanes(curPoint, scd, pl));
        return fstp->getIntersectPolygon(*secp);
    }
}
