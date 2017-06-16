#include "enemyship.h"
#include <iostream>
using namespace std;
Enemy::Enemy(QString filename, int type)
    :active(false),destroyed(false),type(type),file_name(filename)
    {
    image.load(filename);
    box = image.rect();
    switch(type){
    case 1:
    {
        health = 1;
    }
        break;
    case 2:
    {
        health = 3;
        dx = 0;
        dy = 1;
    }
        break;
    case 3:
    {
        health = 1;
        dx = 2;
        dy = 2;
    }
        break;
    case 4:
    {
        health = 30;
        dx = -1;
        dy = 0;
    }
        break;
    default:
    {
        health = 1;
        dx = 0;
        dy = 0;
    }
    }
}
Enemy& Enemy::operator=(const Enemy& e){
    dx = e.dx;
    dy = e.dy;
    health = e.health;
    destroyed = e.destroyed;
    box = e.box;
    image = e.image;
    active = e.active;
    type = e.type;
    return *this;
}

Enemy::~Enemy(){
}
bool Enemy::isDestroyed(){
    return destroyed;
}
Enemy::Enemy(const Enemy &e){
    dx = e.dx;
    dy = e.dy;
    health = e.health;
    destroyed = e.destroyed;
    box = e.box;
    image = e.image;
    active = e.active;
    type = e.type;
}

void Enemy::reset()
{
    if(this->type == 1){
        health = 1;
        box.moveTo(320,300);
    } else {
        box.moveTo(0,0);
        active = false;
    }
}
void Enemy::setDestroyed(bool check){
    destroyed = check;
}

void Enemy::setPosition(int x, int y)
{
    box.moveTo(x,y);
}
void Enemy::setStrafe(int dir){
    if(dir == 1 && dx < 0){dx = this->dx * -1;}
    else if(dir == 0 && dx > 0){dx = this->dx * -1;}
}

bool Enemy::isActive(){
    if(this->isDestroyed() == false){
    return active;}
    else{ return false;}
}
void Enemy::setActive(bool check){
    active = check;
}

QRect Enemy::getArea()
{
    return box;
}

QImage Enemy::getImage()
{
    return image;
}
void Enemy::moveStrafe()
{
    box.translate(dx, dy);
}

void Enemy::moveDown(int d)
{
    box.moveBottom(d);
}

void Enemy::moveUp(int u)
{
    box.moveBottom(u);
}

void Enemy::moveLeft(int l)
{
    box.moveRight(l);
}

void Enemy::moveRight(int r)
{
    box.moveRight(r);
}

void Enemy::decreaseHealth()
{
    health--;
}
int Enemy::getHealth(){
    return health;
}
bool Enemy::checkOutbounds(){
    if(this->getArea().x() < 0 || this->getArea().x() > 640 || this->getArea().y() > 500 || this->getArea().y() < 0){
        return true;
    }else{
        return false;
    }
}
