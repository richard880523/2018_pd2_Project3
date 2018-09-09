#include "Boss.h"
#include <QList>

extern int Phealth;
Boss::Boss(){

}
void Boss::shoot(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i=0,n = colliding_items.size(); i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)){           
            Phealth-=2;
            if(Phealth < 0)
                Phealth = 0;
            //remove the bomb
            scene()->removeItem(this);
            //delete the bomb
            delete this;
            return;
        }
    }
    setPos(x(), y()+1);
    if(y() > 680){
        this->scene()->removeItem(this);
        delete this;
    }
}
void Boss::critical(){
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i=0,n = colliding_items.size(); i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)){           
            Phealth-=5;
            if(Phealth < 0)
                Phealth = 0;
            //remove the bomb
            scene()->removeItem(this);
            //delete the bomb
            delete this;
            return;
        }
    }
    setPos(x(), y()+2);
    if(y() > 680){
        this->scene()->removeItem(this);
        delete this;
    }
}
