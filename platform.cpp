#include "platform.h"
#include <Windows.h>
#include <QGraphicsScene>

Platform::Platform(qreal width,qreal height,Game*game,qreal radius)
    :MovableElement(game,20,0)
{
    this->radius=radius;
    this->width=width;
    this->height=height;
}
Platform::~Platform()
{

}
QRectF Platform::boundingRect() const{
    if(game->getBonus()==WIDE_PLATFORM){
        return QRectF(0,0,1.5*width+2*radius,height);
    }
    return QRectF(0,0,width+2*radius,height);
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem * , QWidget *){
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(Qt::gray);
    if(game->getBonus()==WIDE_PLATFORM){
        painter->drawRect(radius,0,1.5*width,height);
        painter->drawEllipse(0,0,2*radius,2*radius);
        painter->drawEllipse(1.5*width,0,2*radius,2*radius);
    }
    else{
        painter->drawRect(radius,0,width,height);
        painter->drawEllipse(0,0,2*radius,2*radius);
        painter->drawEllipse(width,0,2*radius,2*radius);
    }
}
qreal Platform::getHeight(){
    return height;
}
qreal Platform::getRadius(){
    return radius;
}

qreal Platform::getWidth(){
    return width;
}
void Platform::advance(int step)
{
    if(!step)
        return;
    QPointF point(mapToScene(0,0));
    if(GetKeyState(VK_RIGHT)<0){
        if(game->getBonus()==DIRECTION){
            if(point.x()>25){
                this->setPos(mapToParent(-velocity,0));
            }

        }
        else if(point.x()<(scene()->width()-width-25)){
            this->setPos(mapToParent(velocity,0));}
        if(game->canGo()==0){
            QList<QGraphicsItem*>items=scene()->items();
            foreach (QGraphicsItem* item, items) {
                if(dynamic_cast<Ball*>(item)){
                    // QPointF ball_point=item->mapToScene(0,0);
                    item->setPos(mapToParent(velocity+this->width/2-1*item->boundingRect().width(),-1*item->boundingRect().width()));
                }
            }

        }

    }
    else{
        if(GetKeyState(VK_LEFT)<0){
            if(game->getBonus()==DIRECTION){
                if(point.x()<(scene()->width()-width-25)){
                    this->setPos(mapToParent(velocity,0));
                }
            }
            else if(point.x()>25){
                this->setPos(mapToParent(-velocity,0));
            }
            if(game->canGo()==0){
                QList<QGraphicsItem*>items=scene()->items();
                foreach (QGraphicsItem* item, items) {
                    if(dynamic_cast<Ball*>(item)){
                        //  QPointF ball_point=item->mapToScene(0,0);
                        item->setPos(mapToParent(-velocity+this->width/2+1.5*item->boundingRect().width(),-1*item->boundingRect().width()));
                    }

                }
            }}


        update(boundingRect());

    }}

