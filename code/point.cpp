#include "point.h"

point::point()
{
     this->setX(0);
     this->setY(0);
}

point::point(QPoint *p)
{
    this->setX(p->x());
    this->setY(p->y());
}

point::point(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
/*
point* point::qPointToPoint(QPoint p)
{
    point* np = new point(p.x(), p.y());
    return np;
}

int point::getX()
{
    return x;
}

int point::getY()
{
    return y;
}*/

point& point::operator=(point&&p)
{
    this->setX(p.x());
    this->setY(p.y());
    return *this;
}

bool point::operator==(point &p)
{
    return (this->x() == p.x()) && (this->y() == p.y());
}
