#include "life.h"

Life::Life(qreal radius)
{
    this->radius=radius;
}



void Life::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget*){
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(0,0,2*radius,2*radius);
}
QRectF Life::boundingRect() const{
    return QRectF(0,0,2*radius,2*radius);
}
qreal Life::getRadius(){
    return radius;
}

