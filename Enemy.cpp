#include "Enemy.h"
extern int Phealth;
enemy::enemy(){

}
void enemy::fly(){
    /*
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for(int i=0,n = colliding_items.size(); i<n ; ++i){
        if(typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem)){
            Phealth-=2;
            //delete the enemy
            scene()->removeItem(this);
            //delete the enemy
            delete this;
            return;
        }
    }
    */
    setPos(x(), y()+1);
    if(y() > 680){
        this->scene()->removeItem(this);
        delete this;
    }
}
