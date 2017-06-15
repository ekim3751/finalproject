#ifndef ENEMYSHIP_H
#define ENEMYSHIP_H

#include <QRect>
#include <QImage>
#include <QString>


class Enemy{
public:
    Enemy(QString filename, int type);
    Enemy(const Enemy &e);
    Enemy& operator=(const Enemy& e);
    ~Enemy();
    void reset();
    void setPosition(int x, int y);
    QRect getArea();
    QImage getImage();
    bool checkOutbounds();
    void moveDown(int d);
    void moveUp(int u);
    void moveLeft(int l);
    void moveRight(int r);
    void moveStrafe();
    void setStrafe(int dir);
    bool isActive();
    void setActive(bool check);
    bool isDestroyed();
    void setDestroyed(bool check);
    void decreaseHealth();
    int getHealth();
    QString file_name;

protected:
    //
    //
    int dx, dy;
    int health;
    bool destroyed;
    QRect box;
    QImage image;
    bool active;
    int type;
};

#endif // ENEMYSHIP_H
