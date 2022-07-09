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
        QPointF *inter = m->GetIntersectionLineAndSegment(l, *curLine);//m->GetIntersectionSegments(l, *curLine);
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
           if (flag && isPointOnField(*val))
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
        if (!isPointOnField(*pt))
            ptsCnt--;
        else if (p.x() == pt->x() && p.y() == pt->y() && ptsCnt % 2 == 0)
            ptsCnt--;
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


// 1 this polygon in p, -1 - p in this, 0 - no matches
int polygon::isPolygonInPolygon(polygon &p)
{
    bool flag1 = true;
    for (int i = 0; i < p.size(); i++)
    {
        QPointF* curPoint = p.getPointByIndex(i);
        if (!isPointInPolygon(*curPoint))
        {
            flag1 = false;
            break;
        }
    }
    if (flag1)
        return -1;
    bool flag2 = true;
    for (int i = 0; i < vertices.size(); i++)
    {
        QPointF* curPoint = getPointByIndex(i);
        if (!p.isPointInPolygon(*curPoint))
        {
            flag2 = false;
            break;
        }
    }
    if (flag2)
        return 1;
    return 0;
}

polygon* polygon::getIntersectPolygon(polygon &p)
{
    if (isPolygonInPolygon(p) == 1)
    {
        polygon *res = p.getIntersectNestedPolygon(*this);
        res->sortVertices();
        return res;
    }
    else if (isPolygonInPolygon(p) == -1)
    {
        polygon *res = getIntersectNestedPolygon(p);
        res->sortVertices();
        return res;
    }
    QVector<QPointF*> interPoints = GetIntersection(p);
    for (int i = 0; i < p.size(); i++)
    {
        QPointF *curPoint = p.getPointByIndex(i);
        if (isPointInPolygon(*curPoint))
        {
            bool flag = true;
            for (int j = 0; j < interPoints.size();)
            {
                if (vertices[j]->x() == curPoint->x() && vertices[j]->y() == curPoint->y())
                {
                    flag = false;
                    break;
                }
                j++;
            }
            if (flag)
                interPoints.push_back(curPoint);
        }
    }
    polygon *res = new polygon(interPoints);
    res->sortVertices();
    return res;
}

polygon* polygon::getIntersectNestedPolygon(polygon &smol)
{
    //needed?
    sortVertices();
    smol.sortVertices();

    //build big polygon with all points
    QVector<QPointF*> allPts;
    for (auto p : vertices)
        allPts.push_back(p);
    for (int i = 0; i < smol.size(); i++)
    {
        QPointF *curPoint = smol.getPointByIndex(i);
        bool flag = true;
        for (int j = 0; j < allPts.size(); j++)
        {
            if (allPts[j]->x() == curPoint->x() && allPts[j]->y() == curPoint->y())
            {
                flag = false;
                break;
            }
        }
        if (flag)
            allPts.push_back(curPoint);
    }
    polygon* megaPol = new polygon(allPts);
    megaPol->sortVertices();
    allPts = megaPol->getVertices();

    //get unique vertices for big polygon

    QVector<QPointF*> pts;
    for (int i = 0; i < allPts.size(); i++)
    {
        QPointF *curPoint = megaPol->getPointByIndex(i);
        if (!smol.isPointInPolygon(*curPoint))
            pts.push_back(curPoint);
    }
    int fstPointIndex, lastPointIndex, ind1 = 0;
    int a  = allPts.indexOf(pts[0]);
    //get neighbour with unigue common point
    do
        {

            fstPointIndex = abs(a + ind1) % megaPol->size();//smol.size();//(a + ind1) % smol.size();
            QPointF *curPoint = megaPol->getPointByIndex(fstPointIndex);
            if (smol.isPointInPolygon(*curPoint))
                break;

            if (abs(ind1) == megaPol->size())
                break;//return new polygon(pts);
            ind1++;
        } while (1);
    int b  = allPts.indexOf(pts.last()), ind2 = 0;
    //get neighbour with unigue common point
    do
        {

            lastPointIndex = abs(b + ind2)% megaPol->size();// % smol.size();
            QPointF *curPoint = megaPol->getPointByIndex(lastPointIndex);
            if (smol.isPointInPolygon(*curPoint) && ((fabs(curPoint->x() - allPts[fstPointIndex]->x()) >= (10e-4))
                    || (fabs(curPoint->y() - allPts[fstPointIndex]->y()) >= (10e-4))))
                break; //point found

            if (abs(ind2) == megaPol->size())
                break;//return new polygon(pts);
            ind2--;
        } while (1);


    pts.push_back(allPts[fstPointIndex]);
    pts.push_back(allPts[lastPointIndex]);
    //build polygon
    return new polygon(pts);
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
        polygon* res = pl.GetIntersection(curPoint, *halfPerps[0]);
        return res;
    }
    else if (halfPerps.size() == 0)
    {
        polygon* res = &pl;
        return res;
    }
    else
    {
         polygon* res = &pl;
         for (int i = 0; i < halfPerps.size(); i++)
             res = res->GetIntersection(curPoint, *halfPerps[i]);
        /*int mid = halfPerps.size() / 2;
        QVector<QLineF *> fst(halfPerps.begin(), halfPerps.begin() + mid),
                          scd(halfPerps.begin() + mid , halfPerps.end());
        polygon* fstp(getIntersectHalfPlanes(curPoint, fst, pl)),
               * secp(getIntersectHalfPlanes(curPoint, scd, pl));
        return fstp->getIntersectPolygon(*secp);*/
         return res;
    }
}
