#include "locus.h"

locus::locus(QPoint* p, int color)
{
    center = p;
    this->color = color;
}

int locus::getColor()
{
    return color;
}

QPoint* locus::getPoint()
{
    return center;
}

