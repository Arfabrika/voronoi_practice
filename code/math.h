#ifndef MATH_H
#define MATH_H

#include <QObject>
#include <QLine>
#include <point.h>

class math : public QObject
{
    Q_OBJECT
public:
    math();
    bool isPointOnSegment(QLine &l, point &p);
    point* GetIntersectionLines(QLine &l1, QLine&l2);
    point* GetIntersectionSegments(QLine &l1, QLine&l2);
};

#endif // MATH_H
