#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QLCDNumber>
#include <QLabel>
#include "game.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //MainWindow();
private:
    Ui::MainWindow *ui;
    QLabel *createLabel(const QString &text);

    Game *game;
    QLCDNumber *score;
    QLCDNumber *lives;
    QLCDNumber *accuracy;

    QLabel *scorelabel;
    QLabel *liveslabel;
    QLabel *accuracylabel;

    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;

};

#endif // MAINWINDOW_H
