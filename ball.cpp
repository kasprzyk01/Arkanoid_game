#include "ball.h"
#include <QGraphicsScene>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "platform.h"
#include "bonus.h"

Ball::Ball(qreal radius,Game*game)
    :MovableElement(game,10,315)
{

    this->radius=radius;
    this->destroyed=0;


}
Ball::~Ball()
{

}
QRectF Ball::boundingRect() const{
    return QRectF(0,0,2*radius,2*radius);
}
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->setBrush(Qt::SolidPattern);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(0,0,2*radius,2*radius);
}
qreal Ball::getRadius(){
    return radius;
}
QPainterPath Ball::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
void Ball::advance(int step){

    if(game->canGo()==1){

        if(!step){
            return;}
        QPointF ball_point(mapToScene(0,0));


        if((ball_point.x()>=(scene()->width()-20)) && direction>=270 && direction<360){
            direction=270-(360-direction);
            while(direction>360){
                direction=direction-360;}
            while(direction<0){
                direction=direction+360;}}

        else if(ball_point.x()>=(scene()->width()-20) && direction>0 && direction<90){
            direction=90+direction;
            while(direction>360){
                direction=direction-360;        }
            while(direction<0){
                direction=direction+360;}    }

        if(ball_point.x()<20 && direction>180 && direction<270 ){
            direction=direction+90;
            while(direction>360){
                direction=direction-360;
            }
            while(direction<0){
                direction=direction+360;
            }
        }

        if(ball_point.x()<20 && direction>90 && direction<180 ){
            direction=90-(180-direction);
            while(direction>360){
                direction=direction-360;
            }
            while(direction<0){
                direction=direction+360;
            }
        }

        if((ball_point.y()<10) && direction>=270 && direction<360){
            direction=40;
            while(direction>360){
                direction=direction-360;
            }
            while(direction<0){
                direction=direction+360;
            }
        }

        if((ball_point.y()<10) && direction>=180 && direction<=270){
            direction=(270-direction)+90;
            while(direction>360){
                direction=direction-360;
            }
            while(direction<0){
                direction=direction+360;
            }
        }

        /*if(ball_point.y()>(scene()->height()-20) && direction>0 && direction<90){
        direction=-direction;
        while(direction>360){
            direction=direction-360;
        }
        while(direction<0){
            direction=direction+360;
        }
    }

    if(ball_point.y()>(scene()->height()-20) && direction>90 && direction<180){
        direction=270-(direction-90);
        while(direction>360){
            direction=direction-360;
        }
        while(direction<0){
            direction=direction+360;
        }
    }*/
        if(ball_point.y()>(scene()->height()+20))
        {

            game->sound("C:/Users/krzysztof/Desktop/arkangameover.aif");
            QList<QGraphicsItem*>items=scene()->items();
            foreach (QGraphicsItem* item, items) {
                if(dynamic_cast<Life*>(item)){
                    delete item;
                    return;

                }}
           //delete this
            game->gameOver();
            return;


        }

        Q_ASSERT(scene());
        QList<QGraphicsItem*> items=scene()->collidingItems(this);
        foreach (QGraphicsItem*item,items){
            if(dynamic_cast<Platform*>(item)){
                QPointF platform_point=item->mapToScene(0,0);
                if(ball_point.x()>platform_point.x() && ball_point.x()< (platform_point.x() + (item->boundingRect().width()/2)) &&
                        ball_point.y()+2*radius>=platform_point.y()){
                    direction=225;
                    game->sound("C:/Users/krzysztof/Desktop/arkanpaletka.aif");


                }
                if(ball_point.x()>platform_point.x()+item->boundingRect().width()/2 &&
                        ball_point.x()<platform_point.x()+item->boundingRect().width()
                        && ball_point.y()+2*radius>=platform_point.y()){
                    direction=315;
                    game->sound("C:/Users/krzysztof/Desktop/arkanpaletka.aif");

                }
            }

            else if(Brick* brick = dynamic_cast<Brick*>(item)){

                if(item == collided_brick){
                    collision_number --;
                }else{
                    collision_number = 0;
                    collided_brick = NULL;
                }
                if(collision_number<1){
                QPointF brick_point=item->mapToScene(0,0);
                if(direction>90 && direction<180){

                    if (brick_point.y() < ball_point.y() + 2*radius){
                        direction=direction-90+180;
                        while(direction>360){
                            direction=direction-360;        }
                        while(direction<0){
                            direction=direction+360;}
                        brick->decrementLife();
                        collided_brick=item;
                        if(brick->getLife()<1){
                            delete item;
                            game->brickDestroyed();
                            destroyed++;
                        }
                        else{
                            brick->update(brick->boundingRect());
                        }


                        game->sound("C:/Users/krzysztof/Desktop/arkanbloczek.aif");


                        if(destroyed%5==0){
                            bonus=new Bonus(20,20,game);
                            bonus->setPos(brick_point.x()+brick->getWidth()/2-bonus->getWidth()/2,brick_point.y()+brick->getHeight()/2);
                            scene()->addItem(bonus);

                        }

                    }}
                else if(direction>0 && direction<90){
                    if (brick_point.y() < ball_point.y() + 2*radius){
                        direction=-direction;
                        while(direction>360){
                            direction=direction-360;        }
                        while(direction<0){
                            direction=direction+360;}
                        brick->decrementLife();
                        collided_brick=item;
                        if(brick->getLife()<1){
                            delete item;
                            game->brickDestroyed();
                            destroyed++;
                        }
                        else{
                            brick->update(brick->boundingRect());
                        }

                        game->sound("C:/Users/krzysztof/Desktop/arkanbloczek.aif");



                        if(destroyed%5==0){
                            bonus=new Bonus(20,20,game);
                            bonus->setPos(brick_point.x()+brick->getWidth()/2-bonus->getWidth()/2,brick_point.y()+brick->getHeight()/2);
                            scene()->addItem(bonus);

                        }

                    }
                }
                else if(direction>270 && direction<360){
                    if(brick_point.y()+2*radius>ball_point.y()){
                        direction=360-direction;
                        while(direction>360){
                            direction=direction-360;        }
                        while(direction<0){
                            direction=direction+360;}
                        brick->decrementLife();
                        if(brick->getLife()<1){
                            delete item;
                            game->brickDestroyed();
                            collided_brick=item;
                            destroyed++;
                        }
                        else{
                            brick->update(brick->boundingRect());
                        }

                        game->sound("C:/Users/krzysztof/Desktop/arkanbloczek.aif");


                        if(destroyed%5==0){
                            bonus=new Bonus(20,20,game);
                            bonus->setPos(brick_point.x()+brick->getWidth()/2-bonus->getWidth()/2,brick_point.y()+brick->getHeight()/2);
                            scene()->addItem(bonus);


                        }
                    }
                }
                else if(direction>180 && direction<270){
                    if(brick_point.y()+2*radius>ball_point.y()){
                        direction=270-direction+90;
                        while(direction>360){
                            direction=direction-360;        }
                        while(direction<0){
                            direction=direction+360;}
                        brick->decrementLife();
                        if(brick->getLife()<1){
                            delete item;
                            game->brickDestroyed();
                            collided_brick=item;
                            destroyed++;
                        }
                        else{
                            brick->update(brick->boundingRect());
                        }}


                        game->sound("C:/Users/krzysztof/Desktop/arkanbloczek.aif");

                        if(destroyed%5==0){
                            bonus=new Bonus(20,20,game);
                            bonus->setPos(brick_point.x()+brick->getWidth()/2-bonus->getWidth()/2,brick_point.y()+brick->getHeight()/2);
                            scene()->addItem(bonus);

                        }
                    }
                }

                 collision_number=2;

            }
        }


        qreal rad_dir=direction*0.0174;
        qreal actual_velocity=velocity;
        if(game->getBonus()==SLOW_BALL){
            actual_velocity=0.5*velocity;
        }
        qreal x = actual_velocity * cos(rad_dir);
        qreal y = actual_velocity * sin(rad_dir);
        setPos(mapToParent(x,y));

    }}
