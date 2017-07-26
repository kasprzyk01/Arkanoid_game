#ifndef LIFE_H
#define LIFE_H
#include<unmovableelement.h>
#include<QPainter>
#include<QPointF>
#include<QRectF>
#include<QGraphicsItem>

///klasa odpowiedzialna za rysowanie żyć gracza

class Life:public UnMovableElement ///dziedziczenie po nieruchomym elemencie
{
private:
    qreal radius; ///promien
public:
    Life(qreal radius); ///konstruktor, inicjuje promień obiektu
    QRectF boundingRect()const; ///funkcja zwracająca prostokąt opisany na obiekcie
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);///funkcja rysująca życia
     ///argumenty opisane w klasie Ball
    qreal getRadius(); ///funkcja zwracająca promień życia
};

#endif // LIFE_H
