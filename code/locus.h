#ifndef LOCUS_H
#define LOCUS_H

#include <QObject>
#include <geometry.h>

class locus : public QObject
{
    Q_OBJECT
public:
    explicit locus(QPoint* p, int color);
    int getColor();
    QPoint* getPoint();
private:
    QPoint* center;
    int color;
};

#endif // LOCUS_H
