#include "brick.h"

Brick::Brick(qreal width,qreal height,QHash<int,QColor>life_color,int life=1)
{
    this->width=width;
    this->height=height;
    this->life_color=life_color;
    this->life=life;
}
Brick::~Brick()
{

}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(life_color[life]);
    painter->drawRect(0,0,width,height);
}
QRectF Brick::boundingRect() const{
    return QRectF(0,0,width,height);
}
qreal Brick::getHeight(){
    return height;
}
qreal Brick::getWidth(){
    return width;
}
int Brick::getLife(){
    return life;
}
void Brick::setLife(int life){
    this->life=life;
}
void Brick::decrementLife(){
    if(life<50){
    life=life-1;}
}
