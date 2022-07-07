#ifndef MATH_H
#define MATH_H

#include <QObject>
#include <geometry.h>

class math : public QObject
{
    Q_OBJECT
    QPointF *infNegPoint;// = new QPointF(INT_MAX, -INT_MAX);
    QPointF *infPoint;// = new QPointF(INT_MAX, INT_MAX);
public:
    math();
    bool isPointOnSegment(QLineF &l, QPointF p);
    QPointF* GetIntersectionLines(QLineF &l1, QLineF&l2);
    QPointF* GetIntersectionSegments(QLineF &l1, QLineF&l2);
    QPointF* GetIntersectionLineAndSegment(QLineF &l, QLineF &seg);
};

#endif // MATH_H
