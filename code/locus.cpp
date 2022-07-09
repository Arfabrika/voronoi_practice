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

void locus::drawLocus(QPainter* painter)
{
    painter->setBrush(QBrush(color, Qt::SolidPattern));
    QVector<QPointF*> vec = p->getVertices();
    QPointF arr[vec.size()];
    for (int j = 0; j < vec.size(); j++)
        arr[j] = *vec[j];
    painter->drawPolygon(arr, p->size(), Qt::OddEvenFill);
   /* painter->setBrush(QBrush(color, Qt::SolidPattern));
    for (int i = 0; i < p->size(); i++)
    {
        int j = (i + 1) % p->size();
        QLineF *curSeg = new QLineF(*p->getPointByIndex(i), *p->getPointByIndex(j));
        painter->drawLine(*curSeg);
    }*/

}
