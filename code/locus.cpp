#include "locus.h"

locus::locus(point* p, int color)
{
    center = p;
    this->color = color;
}

int locus::getColor()
{
    return color;
}

point* locus::getPoint()
{
    return center;
}

