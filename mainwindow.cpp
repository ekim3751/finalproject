#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game(this);
    score = new QLCDNumber(5);
    score->setSegmentStyle(QLCDNumber::Filled);

    lives = new QLCDNumber(2);
    lives->setSegmentStyle(QLCDNumber::Filled);

    accuracy = new QLCDNumber(5);
    accuracy->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, SIGNAL(clicked()), game, SLOT(startGame()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pauseButton, SIGNAL(clicked()), game, SLOT(pauseGame()));
    connect(game, SIGNAL(scoreChanged(int)), score, SLOT(display(int)));
    connect(game, SIGNAL(livesChanged(int)), lives, SLOT(display(int)));
    connect(game, SIGNAL(accuracyChanged(double)), accuracy, SLOT(display(double)));

    QWidget *widget = new QWidget();
    QGridLayout *layout = new QGridLayout;
    scorelabel = new QLabel("Score",widget);
    liveslabel = new QLabel("Lives",widget);
    accuracylabel = new QLabel("Accuracy",widget);

    layout->addWidget(game, 0, 0, 10, 3, 0);
    layout->addWidget(score, 11, 0, 0);
    layout->addWidget(lives, 11, 2, 0);
    layout->addWidget(accuracy, 11, 1, 0);
    layout->addWidget(scorelabel, 11, 0, 0);
    layout->addWidget(liveslabel, 11, 2, 0);
    layout->addWidget(accuracylabel, 11, 1, 0);
    layout->addWidget(startButton, 13, 0, 0);
    layout->addWidget(pauseButton, 13, 1, 0);
    layout->addWidget(quitButton, 13, 2, 0);
    layout->setRowStretch(0, 30);
    layout->setRowStretch(11, 3);
    layout->setRowStretch(12, 0);
    layout->setRowStretch(13, 3);

    widget->setLayout(layout);
    setCentralWidget(widget);


    setWindowTitle(tr("Space Invaders"));
    QMainWindow::resize(640, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}
