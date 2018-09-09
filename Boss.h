#ifndef BOSS_H
#define BOSS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
//#include <QProgressBar>

class Boss : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Boss();
public slots:
    void shoot();
    void critical();
};

#endif // BOSS_H
