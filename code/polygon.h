#ifndef POLYGON_H
#define POLYGON_H

#include <QObject>

class polygon : public QObject
{
    Q_OBJECT
public:
    polygon();
    polygon(QVector<QPointF*> v);
    int size();
    QPointF* getPointByIndex(int ind);
    QVector<QPointF*> getVertices();
    QVector<QPointF*> GetIntersection(QLineF &l);
    QVector<QPointF*> GetIntersectionRay(QLineF &ray);
    polygon* GetIntersection(QPointF &pt, QLineF &l);
    bool isPointInPolygon(QPointF &p);
    bool isPointOnField(QPointF &p);
    polygon* getIntersectHalfPlanes(QPointF &curPoint, QVector<QLineF*>halfPerps, polygon &pl);
private:
    QVector<QPointF*> vertices;
    void sortVertices();
};

#endif // POLYGON_H
