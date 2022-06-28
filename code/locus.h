#ifndef LOCUS_H
#define LOCUS_H

#include <QObject>
#include <QLine>
#include <point.h>

class locus : public QObject
{
    Q_OBJECT
public:
    explicit locus(point* p, int color);
    int getColor();
    point* getPoint();
private:
    point* center;
    int color;
};

#endif // LOCUS_H
