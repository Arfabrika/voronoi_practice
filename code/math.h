#ifndef MATH_H
#define MATH_H

#include <QObject>
#include <geometry.h>

class math : public QObject
{
    Q_OBJECT
public:
    math();
    bool isPointOnSegment(QLine &l, QPoint p);
    QPoint* GetIntersectionLines(QLine &l1, QLine&l2);
    QPoint* GetIntersectionSegments(QLine &l1, QLine&l2);
};

#endif // MATH_H
