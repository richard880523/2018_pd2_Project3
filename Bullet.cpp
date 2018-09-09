#include "Bullet.h"
#include <QList>

extern int score;
extern int Bhealth;
extern int energy;
bullet::bullet(){
}
void bullet::fly(){
    //collide enemy
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i=0,n = colliding_items.size(); i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(enemy)){
            score++;
            energy+=5;
            //remove them both
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            //delete them both
            delete colliding_items[i];
            delete this;
            return;
        }
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)){
            score+=3;
            energy+=1;
            Bhealth--;
            if(Bhealth < 0)
                Bhealth = 0;
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    setPos(x(), y() - 3);
    if(y() < 0){
        this->scene()->removeItem(this);
        delete this;
    }
}
void bullet::ultimateFly(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i=0,n = colliding_items.size(); i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(enemy)){
            score++;
            energy+=5;
            //remove the enemy
            scene()->removeItem(colliding_items[i]);
            //delete the enemy
            delete colliding_items[i];
            return;
        }
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)){
            score+=3;
            energy+=1;
            Bhealth-=5;
            if(Bhealth < 0)
                Bhealth = 0;
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    setPos(x(), y() - 3);
    if(y() < 0){
        this->scene()->removeItem(this);
        delete this;
    }
}
