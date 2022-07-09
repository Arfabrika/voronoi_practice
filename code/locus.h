#ifndef LOCUS_H
#define LOCUS_H

#include <QObject>
#include <geometry.h>
#include <QPainter>

class locus : public QObject
{
    Q_OBJECT
public:
    explicit locus(QPointF* cent, polygon *pl, int color);
    int getColor();
    QPointF* getPoint();
    void drawLocus(QPainter* painter);
private:
    QPointF* center;
    int color;
    polygon* p;
};

#endif // LOCUS_H
