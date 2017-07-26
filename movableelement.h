#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H
#include "element.h"
#include "game.h"


class MovableElement:public Element
{
public:
    MovableElement(Game *game,qreal velocity,qreal direction); ///konstruktor, inicjuje wskaźnik na grę, prędkość, kierunek
    ~MovableElement(); ///destruktor
protected:
    Game*game;
    qreal velocity;
    qreal direction;
};

#endif // MOVABLEELEMENT_H
