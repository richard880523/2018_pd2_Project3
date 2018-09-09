#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "Enemy.h"
#include "Boss.h"

class bullet : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    bullet();

public slots:
    void fly();
    void ultimateFly();
};

#endif // BULLET_H
