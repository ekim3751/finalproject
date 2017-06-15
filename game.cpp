#include "game.h"
#include <QPainter>
#include <QApplication>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>
using namespace std;

Game::Game(QWidget *parent):QWidget(parent){

    setFocusPolicy(Qt::StrongFocus);
    try{ //account for exceptions (RAII)
        player = new Enemy("/Users/Elliot/finalproj/alienhead.png",1);
        player->setActive(true);
        for(int i = 0; i < 40; i++){
            playerammo[i] = new Weapon("/Users/Elliot/finalproj/bullet.png",0,-2);
        }
        playerhaterboss = new Enemy("/Users/Elliot/finalproj/alienboss.png",4);

        for(int i = 0; i < 10; i++){
            playerhater[i] = new Enemy("/Users/Elliot/finalproj/alien.png",2);
            playerhatertwo[i] = new Enemy("/Users/Elliot/finalproj/alien2.png",3);
            enemyammo[i] = new Weapon("/Users/Elliot/finalproj/missile.png",0,2);
            enemyammotwo[i] = new Weapon("/Users/Elliot/finalproj/homing.png",0,3);
            bossammo[i] = new Weapon("/Users/Elliot/finalproj/bomb.png",0,3);
        }
    }
    catch( std::exception &e ){
            std::cerr << "Error\n";
            player = nullptr;
            for(int i = 0; i < 40; i++){
                playerammo[i] = nullptr;
            }
            playerhaterboss = nullptr;

            for(int i = 0; i < 10; i++){
                playerhater[i] = nullptr;
                playerhatertwo[i] = nullptr;
                enemyammo[i] = nullptr;
                enemyammotwo[i] = nullptr;
                bossammo[i] = nullptr;
            }
            throw;
    }
    xShooter = 0;
    gameOver = false;
    gameWon = false;
    paused = false;
    gameStarted = false;
    timerIdShip = 0;
    timerIdShiptwo = 0;
    timerIdShipboss = 0;
    shotcount = 0;
    hitcount = 0;
    accuracy = 0;
    score = 0;
    lives = 5;
    setPalette(QPalette(Qt::GlobalColor(Qt::black)));
    setAutoFillBackground(true);
}
Game& Game::operator=(const Game& g){
    delete player;
    this->player = new Enemy(*(g.player));
    for(int i = 0; i < 40; i++){
        delete playerammo[i];
        //Enemy *temp = g.playerammo[i];
        this->playerammo[i] = new Weapon(*(g.playerammo[i]));
    }
    playerhaterboss = new Enemy(*(playerhaterboss));

    for(int i = 0; i < 10; i++){
        playerhater[i] = new Enemy(*(g.playerhater[i]));
        playerhatertwo[i] = new Enemy(*(g.playerhatertwo[i]));
        enemyammo[i] = new Weapon(*(g.enemyammo[i]));
        enemyammotwo[i] = new Weapon(*(g.enemyammotwo[i]));
        bossammo[i] = new Weapon(*(g.bossammo[i]));
    }
    return *this;
}
Game::~Game(){ //follows RAII: heap memory is deleted when game goes out of scope
    delete player;
    for (int i = 0; i < 10; i++)
    {
        delete enemyammo[i];
        delete enemyammotwo[i];
        delete bossammo[i];
        delete playerhater[i];
        delete playerhatertwo[i];
    }
    for (int i = 0; i < 40; i++)
    {
        delete playerammo[i];
    }
    delete playerhaterboss;
}
void Game::paintEvent(QPaintEvent *event){
    painter.begin(this);
    if (gameOver)
    {
      QFont font("Courier", 15, QFont::DemiBold);
      QFontMetrics fm(font);
      int textWidth = fm.width("Game Over");
      painter.setFont(font);
      int h = 350;
      int w = 600;
      painter.drawText((w/2)-textWidth/2, h/2, "Game Over");
    }
    else if(gameWon)
    {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        painter.setFont(font);
        int h = 350;//height();
        int w = 600;//width();
        int textWidth = fm.width("Victory!");
        painter.drawText((w/2)-textWidth/2, h/2, "Victory!");
    }
    else
    {
        drawStuff<Enemy,&Enemy::getArea,&Enemy::getImage,&Enemy::isActive>(player);
        std::for_each(std::begin(playerhater),std::end(playerhater),[this](Enemy* value){drawStuff<Enemy,&Enemy::getArea,&Enemy::getImage,&Enemy::isActive>(value);});
        std::for_each(std::begin(playerhatertwo),std::end(playerhatertwo),[this](Enemy* value){drawStuff<Enemy,&Enemy::getArea,&Enemy::getImage,&Enemy::isActive>(value);});
        std::for_each(std::begin(playerammo),std::end(playerammo),[this](Weapon* value){drawStuff<Weapon,&Weapon::getRect,&Weapon::getImage,&Weapon::isActive>(value);});
        std::for_each(std::begin(enemyammo),std::end(enemyammo),[this](Weapon* value){drawStuff<Weapon,&Weapon::getRect,&Weapon::getImage,&Weapon::isActive>(value);});
        std::for_each(std::begin(enemyammotwo),std::end(enemyammotwo),[this](Weapon* value){drawStuff<Weapon,&Weapon::getRect,&Weapon::getImage,&Weapon::isActive>(value);});
        std::for_each(std::begin(bossammo),std::end(bossammo),[this](Weapon* value){drawStuff<Weapon,&Weapon::getRect,&Weapon::getImage,&Weapon::isActive>(value);});
        drawStuff<Enemy,&Enemy::getArea,&Enemy::getImage,&Enemy::isActive>(playerhaterboss);
    }
    painter.end();
}
void Game::timerEvent(QTimerEvent *event){
    ++timerIdShip;
    ++timerIdShiptwo;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 639);
    std::uniform_int_distribution<> distwo(1, 100);
    std::for_each(std::begin(playerhater),std::end(playerhater),[this](Enemy* value){moveStuff<Enemy,&Enemy::moveStrafe,&Enemy::isActive>(value);});
    std::for_each(std::begin(playerhater),std::end(playerhater),[this](Enemy* value){moveStuff<Enemy,&Enemy::reset,&Enemy::checkOutbounds>(value);});
    std::for_each(std::begin(playerhatertwo),std::end(playerhatertwo),[this](Enemy* value){moveStuff<Enemy,&Enemy::moveStrafe,&Enemy::isActive>(value);});
    std::for_each(std::begin(playerhatertwo),std::end(playerhatertwo),[this](Enemy* value){moveStuff<Enemy,&Enemy::reset,&Enemy::checkOutbounds>(value);});
    std::for_each(std::begin(playerammo),std::end(playerammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::autoMove,&Weapon::isActive>(value);});
    std::for_each(std::begin(playerammo),std::end(playerammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::resetState,&Weapon::checkOutbounds>(value);});
    std::for_each(std::begin(enemyammo),std::end(enemyammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::autoMove,&Weapon::isActive>(value);});
    std::for_each(std::begin(enemyammo),std::end(enemyammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::resetState,&Weapon::checkOutbounds>(value);});
    std::for_each(std::begin(enemyammotwo),std::end(enemyammotwo),[this](Weapon* value){moveStuff<Weapon,&Weapon::autoMove,&Weapon::isActive>(value);});
    std::for_each(std::begin(enemyammotwo),std::end(enemyammotwo),[this](Weapon* value){moveStuff<Weapon,&Weapon::resetState,&Weapon::checkOutbounds>(value);});
    std::for_each(std::begin(bossammo),std::end(bossammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::autoMove,&Weapon::isActive>(value);});
    std::for_each(std::begin(bossammo),std::end(bossammo),[this](Weapon* value){moveStuff<Weapon,&Weapon::resetState,&Weapon::checkOutbounds>(value);});

    for(int i = 0; i < 10; i++){
        if(enemyammo[i]->isActive() == false && playerhater[i]->isActive() == true){
            if(distwo(gen) == 1){
                enemyammo[i]->setActive(true);
                enemyammo[i]->setPosition(playerhater[i]->getArea().x() + 20, playerhater[i]->getArea().y() + 20);
            }
        }
        if(enemyammotwo[i]->isActive() == false && playerhatertwo[i]->isActive() == true){
            if(distwo(gen) == 1){
                enemyammotwo[i]->setActive(true);
                enemyammotwo[i]->setPosition(playerhatertwo[i]->getArea().x() + 20, playerhatertwo[i]->getArea().y() + 20);
            }
        }
    }
    if (playerhaterboss->isActive() == true)
    {
        playerhaterboss->moveStrafe();
    }
    if(timerIdShip == 100){ //which
        for(int i = 0; i < 10; i++){
            if(playerhater[i]->isActive() == false && playerhater[i]->isDestroyed() == false){
                playerhater[i]->setPosition(dis(gen),0);
                playerhater[i]->setActive(true);
                break;
            }
        }
        timerIdShip = 0;
    }
    if(timerIdShiptwo == 250){ //which
        for(int i = 0; i < 10; i++){
            if(playerhatertwo[i]->isActive() == false && playerhatertwo[i]->isDestroyed() == false){
                playerhatertwo[i]->setActive(true);
                playerhatertwo[i]->setPosition(dis(gen),0);
                if(playerhatertwo[i]->getArea().x() < 320){playerhatertwo[i]->setStrafe(1);
                } else{playerhatertwo[i]->setStrafe(0);}
                break;
            }
        }
        timerIdShiptwo = 0;
    }
    if(score == 20 && playerhaterboss->isActive()==false){
        playerhaterboss->setActive(true);
        playerhaterboss->setPosition(320,100);
    }
    if(playerhaterboss->isActive() == true){
        ++timerIdShipboss;
        if(timerIdShipboss == 10){
            for(int i = 0; i < 10; i++){
                if(bossammo[i]->isActive() == false){
                 bossammo[i]->setActive(true);
                 bossammo[i]->setPosition(playerhaterboss->getArea().x() + 20, playerhaterboss->getArea().y() + 20);
                 if(bossammo[i]->getXDir() < 4 && bossammo[i]->getXDir() > -4){
                     if(playerhaterboss->getArea().x() < player->getArea().x()){
                         bossammo[i]->setXDir(bossammo[i]->getXDir()+1);
                     } else{bossammo[i]->setXDir(bossammo[i]->getXDir()-1);}
                 }
                 break;
                }
            }
            timerIdShipboss = 0;
        }
    }
    checkCollision();
    repaint();
}
void Game::keyPressEvent(QKeyEvent *event){
    xShooter = player->getArea().x();
    yShooter = player->getArea().y();
    switch ( event->key() ){
        case Qt::Key_Left :
            if(xShooter > 0){player->moveLeft(xShooter);}
            break;
        case Qt::Key_Right :
            if(xShooter < 590){player->moveRight(xShooter + (2*player->getArea().width()));}
            break;
        case Qt::Key_Up :
            if(yShooter > 0){player->moveUp(yShooter);}
            break;
        case Qt::Key_Down :
            if(yShooter < 350){player->moveDown(yShooter + (2*player->getArea().height()));}
            break;
        case Qt::Key_P :
            pauseGame();
            break;
        case Qt::Key_Space :
            {
                if (gameStarted == false)
                {
                    score = 0;
                    lives = 5;
                    startGame();
                }else{
                    for(int i = 0; i < 40; i++){
                        if(playerammo[i]->isActive() == false){
                            shotcount++;
                            playerammo[i]->setActive(true);
                            playerammo[i]->setPosition(player->getArea().x() + 6, player->getArea().y());
                            break;
                        }
                    }
                }
            }
            break;
        case Qt::Key_Escape:
            {
                qApp->exit();
            }
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
void Game::startGame()
{
    if(gameStarted == false){
        player->reset();
        gameOver = false;
        gameWon = false;
        gameStarted = true;
        timerId = startTimer(10);
        try{
            if(played == true){
                for (int i = 0; i < 10; i++)
                {
                    delete playerhater[i];
                    delete playerhatertwo[i];
                    playerhater[i] = new Enemy("/Users/Elliot/finalproj/alien.png",2);
                    playerhatertwo[i] = new Enemy("/Users/Elliot/finalproj/alien2.png",3);
                }
                delete playerhaterboss;
                playerhaterboss = new Enemy("/Users/Elliot/finalproj/alienboss.png",4);
                score = 0;
                lives = 5;
                hitcount = 0;
                accuracy = 0;
                shotcount = 0;
            }
        }catch( std::exception &e ){
            std::cerr << "Error\n";
            for(int i = 0; i < 40; i++){
                playerammo[i] = nullptr;
            }
            playerhaterboss = nullptr;
            for(int i = 0; i < 10; i++){
                playerhater[i] = nullptr;
                playerhatertwo[i] = nullptr;
            }
        }
        emit scoreChanged(score);
        emit livesChanged(lives);
        emit accuracyChanged(accuracy);
    }
}

void Game::pauseGame()
{
    if (paused)
    {
        timerId = startTimer(10);
        paused = false;
    }
    else
    {
        killTimer(timerId);
        paused = true;
    }
}
void Game::stopGame()
{
    killTimer(timerId);
    gameOver = true;
    gameStarted = false;
    score = 0;
    lives = 0;
}
void Game::victory()
{
    killTimer(timerId);
    gameWon = true;
    gameStarted = false;
}
void Game::checkCollision()
{
    if (!gameOver)
    {
        for (int i=0; i<10; i++)
        {
            for (int j=0; j<40; j++){
                if (playerammo[j]->getRect().intersects(playerhater[i]->getArea()) == true && playerammo[j]->isActive() == true && playerhater[i]->isDestroyed() == false)
                {
                    playerhater[i]->decreaseHealth();
                    playerammo[j]->resetState();
                    hitcount++;
                    if(playerhater[i]->getHealth() == 0){
                        cout<<"Score increased..."<<endl;
                        playerhater[i]->setDestroyed(true);
                        playerhater[i]->reset();

                        //add score
                        score++;
                        emit scoreChanged(score);

                    }
                    //alien->resetState();		//remove later...
                }

                if (playerammo[j]->getRect().intersects(playerhatertwo[i]->getArea()) == true && playerammo[j]->isActive() == true && playerhatertwo[i]->isDestroyed() == false)
                {
                    playerhatertwo[i]->decreaseHealth();
                    playerammo[j]->resetState();
                    hitcount++;
                    if(playerhatertwo[i]->getHealth() == 0){
                        cout<<"Score increased..."<<endl;
                        playerhatertwo[i]->setDestroyed(true);
                        playerhatertwo[i]->reset();
                        //add score
                        score++;

                        emit scoreChanged(score);

                    }
                }

                if (playerammo[j]->getRect().intersects(playerhaterboss->getArea()) == true && playerammo[j]->isActive() == true && playerhaterboss->isDestroyed() == false)
                {
                    playerhaterboss->decreaseHealth();
                    playerammo[j]->resetState();
                    hitcount++;
                    if(playerhaterboss->getHealth() == 0){
                        cout<<"Score increased..."<<endl;
                        playerhaterboss->setDestroyed(true);
                        playerhaterboss->reset();
                                //add score
                        score++;

                        emit scoreChanged(score);

                        victory();
                        played = true;
                    }
                }
                auto accuracyFun = [](int a,int b)->double{ return (static_cast<double>(a)/static_cast<double>(b))*100.0;};
                accuracy = accuracyFun(hitcount,shotcount);
                emit accuracyChanged(accuracy);
            }

            if ((enemyammo[i]->getRect().intersects(player->getArea())) == true && (enemyammo[i]->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                enemyammo[i]->resetState();
                lives--;
                emit livesChanged(lives);
                player->reset();
            }

            if ((enemyammotwo[i]->getRect().intersects(player->getArea())) == true && (enemyammotwo[i]->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                enemyammotwo[i]->resetState();
                lives--;
                emit livesChanged(lives);
                player->reset();
            }
            if ((bossammo[i]->getRect().intersects(player->getArea())) == true && (bossammo[i]->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                bossammo[i]->resetState();
                lives--;
                emit livesChanged(lives);
                player->reset();
            }
            if ((playerhater[i]->getArea().intersects(player->getArea())) == true && (playerhater[i]->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                lives--;
                emit livesChanged(lives);
                player->reset();
            }

            if ((playerhatertwo[i]->getArea().intersects(player->getArea())) == true && (playerhatertwo[i]->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                lives--;
                emit livesChanged(lives);
                player->reset();
            }
            if ((playerhaterboss->getArea().intersects(player->getArea())) == true && (playerhaterboss->isActive() == true))
            {
                cout<<"Life lost..."<<endl;
                lives--;
                emit livesChanged(lives);
                player->reset();
            }
        }
    }
    if (lives == 0)
    {
        stopGame();
        played = true;
    }
}


