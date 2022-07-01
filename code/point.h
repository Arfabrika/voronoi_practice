#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <QPoint>

class point : public QObject, public QPoint
{
    Q_OBJECT
public:
    point();
    point(QPoint *p);
    point(int x, int y);
    /*int getX();
    int getY();
    point* qPointToPoint(QPoint p);*/
    bool operator==(point &p);
    point& operator=(point &&p);
/*private:
    int x, y;
    //int color;*/
};

#endif // POINT_H
