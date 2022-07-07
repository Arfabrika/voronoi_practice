#include "locus.h"

locus::locus(QPointF* cent, polygon *pl, int color)
{
    center = cent;
    this->color = color;
    p = pl;
}

int locus::getColor()
{
    return color;
}

QPointF* locus::getPoint()
{
    return center;
}

void locus::setCenter(QPointF* pt)
{
    center = pt;
}

void locus::setPolygon(polygon *pl)
{
    p = pl;
}

