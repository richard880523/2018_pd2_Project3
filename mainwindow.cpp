#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

int score = 0;
int Phealth = 100;
int Bhealth = 100;
int xboss = 290;
int yboss = 250;
int flag = 1;
int energy = 0;
int count = 0;

bool moveUp, moveDown, moveLeft, moveRight;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0,0,600,700)),//create a scene
    timer(new QTimer),
    tEnemy(new QTimer),
    tBoss(new QTimer),
    tBomb(new QTimer),
    tMove(new QTimer)//constructor
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);//add a view
    player = new QGraphicsPixmapItem(QPixmap(":/res/jet/PixPlane.png"));
    player->setPos(280,580);
    player->setScale(0.75);
    //create an item to put into the scene
    scene->addItem(player);//add an item to the scene    
    timer->start(10);//interval
    tEnemy->start(2000);//interval for spawning enemies
    tBoss->start(100);
    tBomb->start(1300);
    tMove->start(80);
    ui->score->setFont(QFont("NewYork",15));
    ui->health->setFont(QFont("NewYork",15));

    boss = new QGraphicsPixmapItem(QPixmap(":/res/monster/cartoon.png"));
    boss->setPos(250,100);
    scene->addItem(boss);
    ui->Bosshealth->setGeometry(250,330,200,13);
    QPalette p = ui->Bosshealth->palette();
    p.setColor(QPalette::Highlight, Qt::red);
    ui->Bosshealth->setPalette(p);

    ui->Energy_bar->setGeometry(315,755,65,13);
/*
    QPalette q = ui->Playerhealth->palette();
    q.setColor(QPalette::Highlight, Qt::blue);
    ui->Playerhealth->setPalette(q);
*/
    connect(tEnemy,SIGNAL(timeout()),this,SLOT(spawn()));
    connect(tBomb,SIGNAL(timeout()),this,SLOT(Bshoot()));
    connect(timer,SIGNAL(timeout()),this,SLOT(addScore()));
    connect(timer,SIGNAL(timeout()),this,SLOT(Myhealth()));
    connect(tBoss,SIGNAL(timeout()),this,SLOT(BossMove()));
    connect(timer,SIGNAL(timeout()),this,SLOT(addEnergy()));    
    connect(tBoss,SIGNAL(timeout()),this,SLOT(checkhealth()));
    //check boss's health while playing
    connect(tMove,SIGNAL(timeout()),this,SLOT(timerEvent()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(ui->Playerhealth->value() > 0){
        switch(e->key()){
        //case Qt::Key_Up:
        case Qt::Key_W:
            moveUp = true;
        break;
        //case Qt::Key_Down:
        case Qt::Key_S:
            moveDown = true;
        break;
        //case Qt::Key_Left:
        case Qt::Key_A:
            moveLeft = true;
        break;
        //case Qt::Key_Right:
        case Qt::Key_D:
            moveRight = true;
        break;
        case Qt::Key_Space:
            if(energy >= 25){
                ultimate();
                energy -= 25;
            }
        break;
        }
    }
    else
        e->ignore();
}
void MainWindow::keyReleaseEvent(QKeyEvent *e){
    if(ui->Playerhealth->value() > 0){
        switch(e->key()){
            //case Qt::Key_Up:
            case Qt::Key_W:
                moveUp = false;
            break;
            //case Qt::Key_Down:
            case Qt::Key_S:
                moveDown = false;
            break;
            //case Qt::Key_Left:
            case Qt::Key_A:
                moveLeft = false;
            break;
            //case Qt::Key_Right:
            case Qt::Key_D:
                moveRight = false;
            break;
        }
    }
    else
        e->ignore();
}
void MainWindow::timerEvent(){
    if(ui->Playerhealth->value() > 0){
        //case Qt::Key_Up:
        if(moveUp == true)
            if(player->y()-10>0){
                player->setPos(player->x(),player->y() - 10);
                ui->Energy_bar->move(ui->Energy_bar->x(),ui->Energy_bar->y() - 10);//Energy_bar pos fixed
            }
        //case Qt::Key_Down:
        if(moveDown == true){
            if(player->y()+10<600){
                player->setPos(player->x(),player->y() + 10);
                ui->Energy_bar->move(ui->Energy_bar->x(),ui->Energy_bar->y() + 10);
            }
        }
        //case Qt::Key_Left:
        if(moveLeft)
            if(player->x()>0){
                player->setPos(player->x() - 10,player->y());
                ui->Energy_bar->move(ui->Energy_bar->x() - 10,ui->Energy_bar->y());
            }
        //case Qt::Key_Right:
        if(moveRight)
            if(player->x()+100<600){
                player->setPos(player->x() + 10,player->y());
                ui->Energy_bar->move(ui->Energy_bar->x() + 10,ui->Energy_bar->y());
            }
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e){
    if(ui->Playerhealth->value() > 0){
        bullet *b = new bullet;
        b->setScale(0.5);//0.5*original photo
        b->setPixmap(QPixmap(":/res/bullet/OrangeBullet1.png").scaled(50,50));
        b->setPos(player->x() + player->pixmap().width()/2 - b->pixmap().width()/2,player->y()+20 - b->pixmap().height());
        b->connect(timer,SIGNAL(timeout()), b, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    }
    else{
        e->ignore();
    }
}
void MainWindow::ultimate(){
    bullet *b = new bullet;
    b->setScale(0.7);//0.5*original photo
    b->setPixmap(QPixmap(":/res/bullet/blueFireBall.png").scaled(100,100));
    b->setPos(player->x() + player->pixmap().width()/2 - b->pixmap().width()/2,player->y()+20 - b->pixmap().height());
    b->connect(timer,SIGNAL(timeout()), b, SLOT(ultimateFly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}

void MainWindow::spawn(){
    enemy *e = new enemy;

    e->setPixmap(QPixmap(":res/monster/bigEar.svg").scaled(60,60));
    e->setScale(0.8);
    int x = (qrand()%500)+20;
    e->setPos(x,0);
    e->connect(timer,SIGNAL(timeout()), e, SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(e));
}
void MainWindow::Bshoot(){
    Boss *b = new Boss;
    if(qrand()%5 == 0){
        b->setPixmap(QPixmap(":res/bomb/timerBomb3.png").scaled(50,50));
        b->connect(timer,SIGNAL(timeout()), b, SLOT(critical()));
    }
    else{
        b->setPixmap(QPixmap(":res/bomb/bombs.png").scaled(35,35));
        b->connect(timer,SIGNAL(timeout()), b, SLOT(shoot()));
    }
    b->setPos(xboss,yboss+150);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
}
void MainWindow::addScore(){
    ui->score->setText(QString("Score : ") + QString::number(score));
}
void MainWindow::Myhealth(){
    ui->Playerhealth->setValue(Phealth);
}
void MainWindow::BossMove(){

    if(boss->x()>450)
        flag = -1;

    if(boss->x()<20)
        flag = 1;
    xboss = boss->x();
    yboss = boss->y();
    boss->setPos(boss->x()+(10*flag),boss->y());
    ui->Bosshealth->move(ui->Bosshealth->x()+(10*flag),ui->Bosshealth->y());
    ui->Bosshealth->setValue(Bhealth);
}
void MainWindow::addEnergy(){
    ui->Energy_bar->setValue(energy);
}
void MainWindow::checkhealth(){
    if(ui->Bosshealth->value() == 0){
        disconnect(tBomb,SIGNAL(timeout()),this,SLOT(Bshoot()));
        disconnect(tBoss,SIGNAL(timeout()),this,SLOT(BossMove()));
        disconnect(tBoss,SIGNAL(timeout()),this,SLOT(checkhealth()));
        scene->removeItem(boss);
        //delete boss;
        ui->Bosshealth->hide();
        if(count == 0){
            score+=300;
            count++;
        }
        ui->Text->setText("Congratulations!!");
        ui->Text->setStyleSheet("color:lightGray");
        ui->Text->setFont(QFont("times",20));
        ui->Text2->setText("You won");
        ui->Text2->setStyleSheet("color:lightGray");
        ui->Text2->setFont(QFont("Microsoft YaHei",25));
    }
    if(ui->Playerhealth->value() == 0){
        //scene->removeItem(player);
        ui->Text->setText("Oops");
        ui->Text->setStyleSheet("color:lightGray");
        ui->Text->setFont(QFont("times",20));
        ui->Text2->setText("You lose");
        ui->Text2->setStyleSheet("color:lightGray");
        ui->Text2->setFont(QFont("Microsoft YaHei",25));
    }
}
