#ifndef WEAPON_H
#define WEAPON_H

#include <QRect>
#include <QImage>

#include <QString>

using namespace std;


class Weapon
{
public:
    Weapon();
    Weapon(QString filename, int dx, int dy);
    ~Weapon();
    Weapon(const Weapon &w);
    void setPosition(int, int);

    void resetState();

    bool isActive();
    void setActive(bool check);

    QRect getRect();
    void setRect(QRect);
    QImage getImage();
    Weapon& operator=(const Weapon& w);
    void moveTop(int);
    void moveBottom(int);
    void moveRight(int);
    void moveLeft(int);
    bool checkOutbounds();
    void autoMove();

    int getXDir();
    void setXDir(int);
    int getYDir();
    void setYDir(int);

protected:
    QRect rect;
    QImage image;
    QString file_name;
    bool active;
    int xDir;
    int yDir;
};

#endif
