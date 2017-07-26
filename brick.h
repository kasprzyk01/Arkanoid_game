#ifndef BRICK_H
#define BRICK_H
#include <QColor>
#include <QHash>
#include "unmovableelement.h"
#include<QPainter>
///klasa odpowiedzialna za rysowanie klocków, za zmniejszanie żyć klocków po zderzeniu z piłką (funkcja wywołana z klasy piłka)
/// i za ustawianie żyć klocka
class Brick :public UnMovableElement ///dziedziczenie po nieruchomym elemencie
{
public:
    Brick(qreal width,qreal height,QHash<int,QColor>life_color,int life); ///konstruktor inicjujący wysokość, szerokość,
    ///kolor klocka, liczbę żyć klocka
    ~Brick();   ///destruktor
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);///funkcja rysująca klocki
     ///argumenty opisane w klasie Ball
    QRectF boundingRect() const;    ///funkcja zwracająca opisany na klocku prostokąt
    qreal getWidth();               ///funkcja zwracająca szerokość klocka
    qreal getHeight();              ///funkcja zwracająca wysokość klocka
    int getLife();                  ///funkcja zwracająca liczbę żyć klocka
    void decrementLife();           ///funkcja zmniejszająca liczbę żyć klocka po kolizji z piłką
    void setLife(int life);         ///funkcja ustawiająca liczbę żyć klocka, argumentem jest liczba żyć, która pobierana jest
    ///dla każdego klocka z pilku mapa
private:
    qreal width;          ///szerokość klocka
    qreal height;         ///wysokość klocka
    int life;             ///liczba żyć klocka
    QHash<int, QColor> life_color;  ///kolor klocka w zależności od liczby żyć
};

#endif // BRICK_H
