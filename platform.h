#ifndef PLATFORM_H
#define PLATFORM_H
#include <QColor>
#include <QPainter>
#include "movableelement.h"
#include"ball.h"

///klasa odpowiedzialna za rysowanie platformy, jej ruch

class Ball;
class Platform :public MovableElement  ///dziedziczenie prędkości, wskaźnika na grę, kierunku
{
public:
    Platform(qreal width,qreal height,Game*game,qreal radius); ///konstruktor inicjuje szerokość, wysokość, wskaźnik na grę, promień okręgu platformy
    ~Platform(); ///destruktor
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///funkcja rysująca platformę
     ///argumenty opisane w klasie Ball
    QRectF boundingRect()const;     ///funkcja zwracająca prostokąt opisany na platformie
    void advance(int step)Q_DECL_OVERRIDE; ///funkcja obsługująca ruch platformy
    qreal getHeight();  ///funkcja zwracająca wysokość platformy
    qreal getWidth();   ///funkcja zwracająca szerokość platformy
    qreal getRadius();  ///funkcja zwracająca promień okręgu platformy
private:
    qreal radius;   ///promien okręgu platformy
    qreal width;    ///szerokość platformy
    qreal height;   ///wysokość platformy
    Ball *ball;     ///wskaźnik na piłkę

};

#endif // PLATFORM_H
