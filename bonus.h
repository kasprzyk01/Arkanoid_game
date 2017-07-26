#ifndef BONUS_H
#define BONUS_H
#include<movableelement.h>
#include <QColor>
#include <QPainter>
#include"platform.h"

///klasa odpowiedzialna za rysowanie bonusu, losowanie bonusu w konstruktorze, detekcji kolozji bonusu z platformą
class Bonus :public MovableElement ///dziedziczenie prędkości, wskaźnika na grę, kierunku
{
public:
    Bonus(qreal width,qreal height,Game*game); ///konstruktor, inicjuje szerokość, wysokość bonusu i wskaźnik na grę
    ~Bonus(); ///destruktor
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);  ///funkcja rysująca bonus
    ///argumenty opisane w klasie Ball
    void advance(int step) Q_DECL_OVERRIDE;     ///funkcja odpowiedzialna za ruch bonusu i detekcje kolizji z platformą
    QRectF boundingRect() const;                ///funkcja zwracająca opisany na bonusie prostokąt
    BonusType bonus_type;                       /// zmienna typu BonusType
    QColor color;                               ///zmienna typu QColor
    qreal getHeight();                          ///funkcja zwracająca wysokość bonusu
    qreal getWidth();                           ///funkcja zwracająca szerokość bonusu

private:
    qreal width;    ///szerokość bonusu
    qreal height;   ///wysokość bonusu

};

#endif // BONUS_H
