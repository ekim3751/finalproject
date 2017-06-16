#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QKeyEvent>
#include <random>
#include <iostream>
#include <cstdlib>
#include <QPainter>
#include <QApplication>
#include "enemyship.h"
#include "weapon.h"
class Game : public QWidget
{
    Q_OBJECT

public:
    Game(QWidget *parent = 0);
    Game(const Game&& g);
    Game& operator=(const Game& g);

    ~Game(); //follows RAII

protected:
    void paintEvent(QPaintEvent *event); //draws stuff
    void timerEvent(QTimerEvent *event); //updates every 10ms
    void keyPressEvent(QKeyEvent *event); //records user input
    void victory(); //called when boss dies
    void checkCollision(); //records collisions (ships, bullets)
    template<typename P,QRect(P::*func)(),QImage(P::*functwo)(),bool(P::*functhree)()>
    void drawStuff(P* object){
        if((object->*functhree)() == true){ painter.drawImage((object->*func)(),(object->*functwo)());}
    }
    template<typename O,void(O::*func)(),bool(O::*functwo)()>
    void moveStuff(O* object){
        if((object->*functwo)() == true){ (object->*func)();}
    }


public slots:
    void startGame();
    void pauseGame();
    void stopGame();

signals:
    void scoreChanged(int);
    void livesChanged(int);
    void accuracyChanged(double);

private:
    QPainter painter;
    bool played;
    int shotcount;
    int hitcount;
    double accuracy;
    int xShooter;
    int yShooter;
    int timerId;
    int score;
    int lives;
    int timerIdShip;
    int timerIdShiptwo;
    int timerIdShipboss;
    Enemy *player;
    Weapon *playerammo[40]; //array of pointers
    Enemy *playerhater[10];
    Enemy *playerhatertwo[10];
    Enemy *playerhaterboss;
    Weapon *enemyammo[10];
    Weapon *enemyammotwo[10];
    Weapon *bossammo[10];
    bool gameOver;
    bool gameWon;
    bool gameInst;
    bool gameStarted;
    bool paused;
};

#endif // GAME_H
