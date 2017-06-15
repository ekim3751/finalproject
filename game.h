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
    Game& operator=(const Game& g);

    ~Game(); //follows RAII

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void victory();
    void checkCollision();
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
    Weapon *playerammo[40];
    Enemy *playerhater[10];
    Enemy *playerhatertwo[10];
    Enemy *playerhaterboss;
    Weapon *enemyammo[10];
    Weapon *enemyammotwo[10];
    Weapon *bossammo[10];
    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
};

#endif // GAME_H
