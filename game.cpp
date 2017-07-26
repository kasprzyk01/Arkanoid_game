#include <QMessageBox>

#include "game.h"
#include"brick.h"

Game::Game(MainWindow *mainwindow, QGraphicsScene* scene)
    :mainwindow(mainwindow),scene(scene)
{
    this->counter=0;
    this->can_go=0;
    this->lifes=2;
    this->counter=0;
    this->Bonus_time=6000;
}
void Game::setScene(QGraphicsScene *scene){
    this->scene=scene;
}
bool Game::isLevelFinished(){
    QList<QGraphicsItem*>items=scene->items();
    foreach (QGraphicsItem* item, items) {
        if(dynamic_cast<Brick*>(item)){
            return false;
        }
    }
    return true;
}
void Game::brickDestroyed()
{


    if(isLevelFinished()){
        counter=counter+1;
        if(counter==1){
            QMessageBox::information(NULL, "Wiadomość", "Level2");
           // scene->clear();
            can_go=0;
          //  mainwindow->startGame();
            mainwindow->getMap("mapa2.txt");}
        else if(counter==2){
            QMessageBox::information(NULL, "Wiadomość", "Level3");
            //scene->clear();
            can_go=0;
            //mainwindow->startGame();
            mainwindow->getMap("mapa3.txt");
        }
        else if(counter==3){
            QMessageBox::information(NULL, "Wiadomość", "Koniec gry, zacznij od nowa!");
            counter=0;
            //scene->clear();
            can_go=0;
            //mainwindow->startGame();
            mainwindow->getMap("mapa1.txt");


        }

    }

}

void Game::gameOver()
{
    if(lifes==0){
        can_go=0;
        scene->clear();
        QMessageBox::information(NULL, "Wiadomość", "Koniec gry");
    }
    else if(lifes==2){
        lifes--;
        mainwindow->startGame_Life2();
       // QMessageBox::information(NULL, "Wiadomość", "Straciles życie.");
        can_go=0;
    }
    else if(lifes==1){
        lifes--;
        mainwindow->startGame_Life1();
       // QMessageBox::information(NULL, "Wiadomość", "Straciles życie.");
        can_go=0;
    }
}
bool Game::canGo(){
    if(getBonus()==STOP_BALL){
        can_go=0;
    }
    if(can_go==1){
        return true;
    }
    return false;

}
int Game::getBonusTypes(){
    return bonusTypes;
}
BonusType Game::getBonus(){
    return active_bonus;
}
void Game::setBonus(BonusType active_bonus){
    timer2=new QTimer();
    this->active_bonus=active_bonus;
    connect(timer2,SIGNAL(timeout()),this,SLOT(removeBonus()));
    timer2->start(Bonus_time);
}
void Game::removeBonus(){
    if(timer2!=NULL){
        active_bonus=NONE;
        timer2=NULL;
        delete timer2;
        scene->update(scene->sceneRect());
    }
}
void Game::sound(QString file_name1){
    player=new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(file_name1));
    player->setVolume(50);
    player->play();

}






