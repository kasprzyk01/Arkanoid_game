#ifndef BALL_H
#define BALL_H
#include <QColor>
#include <QPainter>
#include "movableelement.h"
#include "brick.h"
#include"bonus.h"
#include"life.h"


///klasa odpowiedzialna jest za rysowanie piłki,ruch piłki, detekcję koizji, logikę odbijania się piłki od ścian i bloczków
class Bonus;
class Ball:public MovableElement  ///dziedziczenie prędkości, wskaźnika na grę, kierunku
{
public:

    Ball(qreal radius,Game*game);   ///konstruktor, zawiera promień piłki i wskaźnik na grę
    ~Ball();                        /// destruktor
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///funkcja rysująca piłkę
    /// argumenty tej funkcji umożliwiają rożne opcje dobrania stylu rysowanego elementu, argument QWidget * widget jest
    /// opcjonalny, wskazuje na widget, który jest aktualnie rysowany
    QRectF boundingRect()const;     ///funkcja zwracająca opisany na piłce prostokąt
    qreal getRadius();              ///funkcja zwracająca promień piłki, który jest prywatny
    void advance(int step)Q_DECL_OVERRIDE;     ///funkcja odpowiedzialna za ruch piłki i kolizje z innymi obiektami
    QPainterPath shape()const;      ///funkcja zwracająca dokładniejszy kształt piłki niż prostokąt
private:
    int collision_number;           ///zmienna zliczająca zderzenia z tym samym klockiem
    qreal radius;                   ///promień piłki
    Bonus*bonus;                    ///wskaźnik na bonus
    int destroyed;                ///zliczanie zbitych klocków
    MainWindow*mainwindow;          ///wskaźnik na mainwindow
    QGraphicsItem *collided_brick;  ///wskaźnik na uderzony przez piłkę klocek
};

#endif // BALL_H
