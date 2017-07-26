#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <cstdlib>
#include <QBrush>
#include <time.h>
#include <QApplication>
#include "movableelement.h"
#include "ball.h"
#include "platform.h"
#include "brick.h"
#include "bonus.h"
#include "life.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),scene(NULL)
{
    ui->setupUi(this);
    game=new Game(this,scene);
    setFixedSize(800,600);
    makeScene();
    startGame();
    startGame_Life3();
    getMap("mapa3.txt");
    setTimer();
    game->sound("C:/Users/krzysztof/Desktop/arkanstart.aif");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::makeScene()
{

    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,795,565);
    game->setScene(scene);
    view=new QGraphicsView();
    view->setScene(scene);
    QPixmap *pixmap=new QPixmap();
    pixmap->load("ark.jpg");
    view->setBackgroundBrush(*pixmap);
    setCentralWidget(view);
}
void MainWindow::startGame(){
    if(scene!=NULL){
        //scene->clear();
        // if(game->lifes==3){
        Platform *platform;
        platform=new Platform(120,26,game,13);
        qreal p_width=platform->getWidth();
        qreal p_height=platform->getHeight();
        qreal x=scene->width()/2-(p_width/2);
        qreal y=scene->height()-(p_height+10);
        platform->setPos(x,y);
        scene->addItem(platform);
        //   }

        Ball*ball;
        ball=new Ball(10,game);
        ball->setPos(x+p_width/2+platform->getRadius()/2,y-ball->getRadius()*2);
        scene->addItem(ball);


    }}
void MainWindow::startGame_Life3(){
    Life *life;
    for(int i=0;i<3;i++){
        life=new Life(8);
        life->setPos(725+i*20,10);
        scene->addItem(life);
    }
}
void MainWindow::startGame_Life2(){
    Life *life;
    for(int i=0;i<2;i++){
        life=new Life(8);
        life->setPos(725+i*20,10);
        scene->addItem(life);
    }
}
void MainWindow::startGame_Life1(){
    Life *life;
    for(int i=0;i<1;i++){
        life=new Life(8);
        life->setPos(725+i*20,10);
        scene->addItem(life);
    }
}


void MainWindow::setTimer(){
    timer1=new QTimer();
    QObject::connect(timer1,SIGNAL(timeout()),scene,SLOT(advance()));
    timer1->start(1000/33);

}
void MainWindow::getMap(QString file_name){
    if(scene!=NULL){
        QFile Plik(file_name);

        if(Plik.open(QIODevice::ReadOnly| QIODevice::Text)){
            QTextStream stream(&Plik);
            QString rowss=stream.readLine();
            QString colss=stream.readLine();
            int rows=rowss.toInt();
            int cols=colss.toInt();
            qreal x=0.1*scene->width();
            qreal x0=x;
            qreal y=0.1*scene->height();
            qreal brick_field_width=0.8*scene->width();
            qreal brick_field_height=0.3*scene->height();
            qreal brick_width=brick_field_width/cols;
            qreal brick_height=brick_field_height/rows;
            QHash<int,QColor>life_color;
            life_color[1]=Qt::darkRed;
            life_color[2]=Qt::darkGreen;
            life_color[3]=Qt::black;
            life_color[4]=Qt::white;
            Brick *brick;
            for(int i=0;i<rows;i++){
                QString row=stream.readLine();
                for(int j=0;j<cols;j++){
                    if(row.at(j)!='0'){
                        brick=new Brick(brick_width,brick_height,life_color,1);
                        brick->setLife(row.at(j).digitValue());
                        brick->setPos(x,y);
                        scene->addItem(brick);
                        x=x+brick_width+4;
                    }
                    if(row.at(j)=='0'){
                        x=x+brick_width+4;
                    }
                }
                x=x0;
                y=y+brick_height+4;

            }
            Plik.close();
        }

    }
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Space){
        game->can_go=1;
    }
}
void MainWindow::disconectAdvance(){
    disconnect(timer1,SIGNAL(timeout()),0,0);
}

