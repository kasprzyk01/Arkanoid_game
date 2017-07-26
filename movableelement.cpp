#include "movableelement.h"

MovableElement::MovableElement(Game*game,qreal velocity,qreal direction)
{
    this->velocity=velocity;
    this->direction=direction;
    this->game=game;

}
MovableElement::~MovableElement(){

}
