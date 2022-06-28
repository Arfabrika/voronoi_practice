#include "point.h"

point::point()
{
    x = y = 0;
}

point* point::qPointToPoint(QPoint p)
{
    point* np = new point(p.x(), p.y());
    return np;
}

point::point(int x, int y)//, int color)
{
    this->x = x;
    this->y = y;
    //this->color = color;
}

int point::getX()
{
    return x;
}

int point::getY()
{
    return y;
}

/*int point::getColor()
{
    return color;
}*/

bool point::operator=(point &p)
{
    return (this->x == p.x) && (this->y == p.y);
}
