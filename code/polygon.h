#ifndef POLYGON_H
#define POLYGON_H

#include <QObject>

class polygon : public QObject
{
    Q_OBJECT
public:
    polygon();
    polygon(QVector<QPoint*> v);
    QVector<QPoint*> GetIntersection(QLine &l);
private:
    QVector<QPoint*> vertices;
};

#endif // POLYGON_H
