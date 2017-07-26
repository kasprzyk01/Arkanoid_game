#ifndef GAME_H
#define GAME_H
#include <QTimer>
#include <QGraphicsScene>
#include <QVector>
#include <QObject>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"
#include<QKeyEvent>
#include<QMediaPlayer>
#include"life.h"

///klasa odpowiedzialna za obsługę gry, odtwarzanie dźwięku w odpowiednich momentach, przechowywanie aktywnego w danym momencie
/// bonusu, ustawianiu wylosowanego bonusu(w klasie bonus) jako aktywny bonus, sprawdzanie czy gra lub level się zakończył i
/// podjęcie odpowiednich działań (przejście do nowego levelu lub zakończenie gry w przypadku skończenia się żyć), kasuje
/// aktywny bonus po skończeniu się czasu jego trwania

class MainWindow;
enum BonusType{     ///typ wyliczeniowy, nowy typ zmiennych BonusType
    NONE=0,         ///wymienione typy bonusów
    WIDE_PLATFORM=1, ///poszerzenie platformy
    SLOW_BALL=2,    ///zwolnienie piłki
    DIRECTION=3,    ///zmiana kierunku przy sterowaniu platformą(naciskając prawą strzałkę platforma jedzie w lewą stronę i odwrotnie)
    STOP_BALL=4     ///powrót piłki na platformę
};

class Game:public QObject  ///dziedziczenie po QObject
{
    Q_OBJECT
private:
    QGraphicsScene *scene;   ///wskaźnik na scenę
    MainWindow *mainwindow;  ///wskaźnik na mainwindow
    static const int bonusTypes=4;  ///liczba bonusów(do losowania typu bonusu w konstruktorze klasy Bonus
    QTimer*timer2;            ///wskaźnik na timer odpowiedzialny za wyłączenie bonusu
    int Bonus_time;      ///czas trwania bonusu
    QMediaPlayer *player;     ///wskaźnik na player, do obsługi dźwięku
    int counter;            ///zlicza skończone levele, do wyświetlania odpowiedniej mapy
    Life*life;                ///wskaźnik na życie gracza
    BonusType active_bonus;         /// zmienna typu BonusType, aktywny w danej chwili typ bonusu

public:
    int lifes;            ///liczba żyć gracza -1
    void sound(QString file_name1); ///funkcja odtwarzająca dźwięk z pliku, argument funkcji jest nazwą pliku, który ma być
    ///odtworzony oraz jego lokalizacja
    BonusType getBonus();           ///funkcja zwracająca akywny w danej chwili typ bonusu
    void setBonus(BonusType active_bonus); ///funkcja ustawiająca wylosowany bonus jako aktywny, argumentem jest wylosowany bonus
    Game(MainWindow *main_window , QGraphicsScene* scene);///konstruktor
    void setScene(QGraphicsScene* scene); ///funkcja ustawiająca scene
    int getBonusTypes();        ///funkcja zwracająca liczbę typów bonusów(potrzebna do wylosowania bonusu)
    bool isLevelFinished();     ///funkcja sprawdzająca czy na scenie pozostały klocki
    void brickDestroyed();      ///funkcja wywołana po każdorazowym zbiciu klocka, wywołuje funkcję isLevelFinished(),
    ///odpowiedzialna za przejście do następnych leveli
    void gameOver(); ///funkcja wywoływana gdy piłka spadnie poniżej paletki, sprawdza czy graczowi pozostały jeszcze życia,
    /// jeśli gracz nie ma już żyć to kończy grę
    bool can_go; ///zmienna informująca czy piłka może zacząć ruch(po naciśnięciu spacji zmienia wartość na 1)
    bool canGo();  ///funkcja zwracająca wartość 1 lub 0 w zależności od wartości zmiennej can_go, wykorzystana w klasie Ball


public slots:
    void removeBonus(); ///funkcja wykonywana po upływie czasu odliczanego przez timer2, ustawia NONE za aktywny bonus




};

#endif // GAME_H
