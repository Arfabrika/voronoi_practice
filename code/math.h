#ifndef MATH_H
#define MATH_H

#include <QObject>
#include <geometry.h>

class math : public QObject
{
    Q_OBJECT
    QPointF *infNegPoint;
    QPointF *infPoint;
public:
    math();
    bool isSmaller(float a, float b);
    bool isBigger(float a, float b);
    bool isPointOnSegment(QLineF &l, QPointF p);
    QPointF* GetIntersectionLines(QLineF &l1, QLineF&l2);
    QPointF* GetIntersectionLineAndSegment(QLineF &l, QLineF &seg);
};

#endif // MATH_H
