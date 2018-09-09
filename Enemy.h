#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class enemy : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    enemy();

public slots:
    void fly();
};

#endif // ENEMY_H
