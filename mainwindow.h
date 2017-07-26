#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QPushButton>
#include "game.h"
#include <QMediaPlayer>

///klasa odpowiedzialna za stworzenie nowej gry, ustawienie sceny i widoku, za odświeżanie całej sceny poprzez timer,
/// za wyświetlanie stworzonych w innych klasach obiektów, za pobranie mapy z pliku i wyświetlenie jej, za odłączenie timera
/// w odpowiednim momencie poprzez funkcję disconectAdvance, klasa ta dziedziczy po QMainWindow co umożliwą obsługę klawiszy
/// (funkcja keuPressEvent) oraz łączenie sygnałow i slotów oraz wykorzystanie funkcji mapToScene, mapToParent, które
/// wykorzystywane są przy ruchu obiektów

class Game;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0); ///konstruktor-tworzy nową grę, ustala rozmiar okna, wywołuje funkcje
    /// makescene(), startgame(),setTimer(),getMap()
    ~MainWindow();     ///destruktor
    void makeScene(); /// funkcja tworząca scene, widok, wyświetla tło do rozgrywki, wywoływana w konstruktorze klasy MainWindow
    void startGame_Life3(); ///funkcja wyświetlająca pozostałe życia, wyświetla 3 życia(żółte koła w górnym rogu okna)
    void startGame_Life2(); ///funkcja wyświetlająca pozostałe życia, wyświetla 2 życia
    void startGame_Life1(); ///funkcja wyświetlająca pozostałe życia, wyświetla jedno życie
    void startGame();       ///funkcja tworząca i wyświetlająca piłkę i paletkę
    void setTimer();        ///funkcja tworząca timer, który odświeża funkcję advance()
    void getMap(QString file_name); ///funkcja pobierająca i wyświetlająca mapę z pliku, argumentem jest nazwa pliku
    void disconectAdvance();        ///funkcja rozłączająca timer, który odświeża funkcję advance()


protected:
    void keyPressEvent(QKeyEvent*event); ///funkcja obsługująca klawisz "space", po którego naciśnięciu piłka zaczyna ruch
///argumentem jest event, który w tym przypadku jest wciśnięciem klawisza spacja
private:
    QGraphicsScene *scene;   ///wskaźnik na scenę
    Game *game;             ///wskaźnik na grę
    QGraphicsView *view;    ///wskaźnik na widok
    Ui::MainWindow *ui;
    QTimer *timer1;         ///wskaźnik na timer, który odświeża funkcję advance()

};

#endif // MAINWINDOW_H
