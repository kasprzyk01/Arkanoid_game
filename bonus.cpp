#include "bonus.h"
#include <cstdlib>
#include <time.h>

Bonus::Bonus(qreal width,qreal height,Game*game)
    :MovableElement(game,5,0)
{
    this->width=width;
    this->height=height;
    srand(time(NULL));
    int a=(rand()%game->getBonusTypes()+1);
    if(a==1){
        bonus_type=WIDE_PLATFORM;}
    else if(a==2){
        bonus_type=SLOW_BALL;}
    else if(a==3){
        bonus_type=DIRECTION;}
    else if(a==4){
        bonus_type=STOP_BALL;
    }
    // bonus_type=STOP_BALL;
}
Bonus::~Bonus()
{

}
QRectF Bonus::boundingRect() const{
    return QRectF(0,0,width,height);
}
void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget *){
    QBrush brush;
    switch(bonus_type){
    //default
    case SLOW_BALL:
        color=QColor(Qt::white);
        break;
    case WIDE_PLATFORM:
        color=QColor(Qt::red);
        break;
    case DIRECTION:
        color=QColor(Qt::yellow);
        break;
    case STOP_BALL:
        color=QColor(Qt::magenta);
        break;
    case NONE:
        color=QColor(Qt::black);

    }
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(0,0,width,height);

}
void Bonus::advance(int step){
    if(step==0){
        return;
    }
    QPointF bonus_point(mapToScene(0,0));
    QList<QGraphicsItem*> items = scene()->collidingItems(this);
    foreach(QGraphicsItem* item, items){
        if(Platform* platform2 = dynamic_cast<Platform*>(item)){

            QPointF platform_point=platform2->mapToScene(0,0);
            if(bonus_point.y()>platform_point.y()-platform2->getHeight()){
                game->setBonus(bonus_type);
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
    }
    if(bonus_point.y()>scene()->height()){

        scene()->removeItem(this);
        delete this;
        return;}
    setPos(mapToParent(0,velocity));}
qreal Bonus::getHeight(){
    return height;
}

qreal Bonus::getWidth(){
    return width;
}



