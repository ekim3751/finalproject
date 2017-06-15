#include "mainwindow.h"
#include <QApplication>
#include "game.h"
#include <QDesktopWidget>
void center(QWidget &widget)
{
    int x;
    int y;
    int screenWidth;
    int screenHeight;

    int WIDTH = 600;
    int HEIGHT = 350;

    QDesktopWidget *desktop = QApplication::desktop();

    screenHeight = desktop->height();
    screenWidth = desktop->width();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    widget.setGeometry(x, y, WIDTH, HEIGHT);
    widget.setFixedSize(WIDTH, HEIGHT);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
