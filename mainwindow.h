#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QObject>
#include "Bullet.h"
#include "Enemy.h"
#include "Boss.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    virtual void timerEvent();
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void spawn();
    virtual void Bshoot();
    virtual void addScore();
    virtual void Myhealth();
    virtual void BossMove();
    virtual void ultimate();
    virtual void addEnergy();
    virtual void checkhealth();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;
    QTimer *timer;
    QTimer *tEnemy;
    QTimer *tBoss;
    QTimer *tBomb;
    QTimer *tMove;
    QGraphicsPixmapItem *boss;
};

#endif // MAINWINDOW_H
