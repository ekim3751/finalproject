#include "weapon.h"
#include <iostream>

using namespace std;

Weapon::Weapon(){
    active = false;
}

Weapon::Weapon(QString filename, int dx, int dy)
    :file_name(filename)
{
    image.load(filename);
    rect = image.rect();
    active = false;
    xDir = dx;
    yDir = dy;
}
Weapon::Weapon(const Weapon &w){
    rect = w.rect;
    active = w.active;
    image = w.image;
    xDir = w.xDir;
    yDir = w.yDir;
}

Weapon& Weapon::operator=(const Weapon& w){
    rect = w.rect;
    active = w.active;
    image = w.image;
    xDir = w.xDir;
    yDir = w.yDir;
    return *this;
}

Weapon::~Weapon()
{
    cout<<"Weapon deleted."<<endl;
}

void Weapon::setPosition(int xPos, int yPos)
{
    rect.moveTo(xPos, yPos);
}

void Weapon::resetState()
{
    rect.moveTo(-10,-10);
    active = false;
}

bool Weapon::isActive()
{
    return active;
}
void Weapon::setActive(bool check)
{
    active = check;
}

QRect Weapon::getRect()
{
    return rect;
}
void Weapon::setRect(QRect r)
{
    rect = r;
}
QImage Weapon::getImage()
{
    return image;
}

void Weapon::moveTop(int top)
{
    rect.moveTop(top);
}
void Weapon::moveBottom(int bottom)
{
    rect.moveBottom(bottom);
}
void Weapon::moveRight(int right)
{
    rect.moveRight(right);
}
void Weapon::moveLeft(int left)
{
    rect.moveLeft(left);
}

void Weapon::autoMove()
{
    rect.translate(xDir, yDir);

    /**if (rect.top() <= 10)
    {
        active = false;
    }
    if (rect.bottom() >= 340)
    {
        active  = false;
    }
    if (rect.right() <= 1 || rect.left() >= 599)
    {
        xDir = -xDir;
    } */
}

int Weapon::getXDir()
{
    return xDir;
}
void Weapon::setXDir(int xD)
{
    xDir = xD;
}
int Weapon::getYDir()
{
    return yDir;
}
void Weapon::setYDir(int yD)
{
    yDir = yDir - 1;
}
bool Weapon::checkOutbounds(){
    if(this->getRect().x() < 0 || this->getRect().x() > 640 || this->getRect().y() > 500 || this->getRect().y() < 0){
        return true;
    }else{
        return false;
    }
}

