#ifndef POINT_H
#define POINT_H

#include <QObject>
#include <QPoint>

class point : public QObject
{
    Q_OBJECT
public:
    point();
    point(int x, int y);//, int color);
    int getX();
    int getY();
    point* qPointToPoint(QPoint p);
    bool operator=(point &p);
private:
    int x, y;
    //int color;
};

#endif // POINT_H
