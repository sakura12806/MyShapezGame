#include "playscene.h"
#include "qevent.h"
#include <QDebug>

int playScene::gridSize = 40;

int playScene::minerinterval = 5;
int playScene::conveyorinterval = 5;
int playScene::cutterinterval = 5;
int playScene::transitioninterval = 5;

int playScene::cuttablemineralnum = 0;
int playScene::uncuttablemineralnum = 0;
int playScene::halfmineralnum = 0;
//int playScene::maxX = GAME_WIDTH/gridSize;
//int playScene::maxY = GAME_HEIGHT/gridSize;

playScene::playScene()
{
    this->cursor = new Cursor();
    levelUp = new myPushButton;
    help = new myPushButton;
    backButton();
    setMinerButton();
    setBeltButton();
    setCutterButton();
    setTrashButton();
    setTransitionButton();
    setLevelUpButton();
    setHelpButton();
    //gridSize = SIZE;
    blockInit();
    levelInit();
    //mapUpgradeTimes;
    //totaloperate();
    setTxt(&declaration);
    setTxt(&currentmission1);

    setTxt(&currentmoney);
    operateTimer = new QTimer(this);

    // Connect the timer's timeout signal to the totaloperate slot
    connect(operateTimer, &QTimer::timeout, this, [=](){
        this->totaloperate();
        this->update();
    });

    // Start the timer with a 1000 ms interval (1 second)
    operateTimer->start(1000);

}

void playScene::init(){
    this->cursor = new Cursor();


    playScene::minerinterval = 5;
    playScene::conveyorinterval = 5;
    playScene::cutterinterval = 5;
    playScene::transitioninterval = 5;

    playScene::cuttablemineralnum = 0;
    playScene::uncuttablemineralnum = 0;
    playScene::halfmineralnum = 0;
    money = 0;
    blockInit();
    levelInit();
    ismission1 = false;
    ismission2 = false;
    ismission3 = false;
    isCentreUpgrade = false;
    isMapUpgrade = false;
}
void playScene::blockInit(){

    this->block = *new QVector<QVector<object*>>();
    for(int i =0; i < maxX; i++){
        QVector<object*> temp;
        for(int j=0; j< maxY; j++){
            temp.push_back(new class NullMineral);
        }
        this->block.push_back(temp);
    }
}
//settle object
void playScene::scaleForObject(int start_i, int end_i, int start_j, int end_j, type objecttype){
    qDebug() << "Scaling object";
    if(start_i > end_i || start_j > end_j){
        return;
    }
    for(int i = start_i; i < end_i; i++){
        for(int j = start_j;j< end_j; j++){
            if(i >= maxX || j>= maxY || i<0 || j<0){
                return;
            }
            this->block[i][j]->type = objecttype;
        }
    }
}

//some levels
void playScene::level1(){
    qDebug() << "Entering level1";
    scaleForObject(0, maxX/4, 0, maxY/4, type::cuttableMineral);
    scaleForObject(3 * maxX/4, maxX, maxY/4 * 3 + 2, maxY, type::uncuttableMineral);
    scaleForObject(maxX/2 - 2, maxX/2 +2, maxY/2 -2, maxY/2 +2, type::centre);
    for(int i = 0;i <maxX; i++){
        for(int j = 0; j < maxY; j++){
            if(this->block[i][j]->type == type::centre){
                this->block[i][j] = new class centre;
            }
        }
    }
}
void playScene::upgradecentre(){
    //qDebug() << "Entering level2";
    if(this->isMapUpgrade == false){
        scaleForObject(0, maxX/4, 0, maxY/4, type::cuttableMineral);
        scaleForObject(3 * maxX/4, maxX, maxY/4 * 3 + 2, maxY, type::uncuttableMineral);
        scaleForObject(maxX/2 -3, maxX/2 +3, maxY/2 -3, maxY/2 +3, type::centre);
        for(int i = 0;i <maxX; i++){
            for(int j = 0; j < maxY; j++){
                if(this->block[i][j]->type == type::centre){
                    this->block[i][j] = new class centre;
                }
            }
        }
        this->isCentreUpgrade = true;
    }
    else{
        scaleForObject(0, maxX/4 + 1, 0, maxY/4, type::cuttableMineral);
        scaleForObject(3 * maxX/4, maxX, maxY/4 * 3 + 2, maxY, type::uncuttableMineral);
        scaleForObject(0, maxX/12 , maxY/4 * 3, maxY, type::cuttableMineral);
        scaleForObject(maxX/12 , maxX/12 + 3, maxY/4 * 3, maxY, type::uncuttableMineral);
        scaleForObject(maxX/2 - 3, maxX/2 + 4, maxY/2 - 3, maxY/2 + 4, type::centre);
        for(int i = 0;i <maxX; i++){
            for(int j = 0; j < maxY; j++){
                if(this->block[i][j]->type == type::centre){
                    this->block[i][j] = new class centre;
                }
            }
        }
        this->isCentreUpgrade = true;
    }
}

void playScene::upgrademap(){
    scaleForObject(0, maxX/4 + 1, 0, maxY/4, type::cuttableMineral);
    scaleForObject(3 * maxX/4, maxX, maxY/4 * 3 +2, maxY, type::uncuttableMineral);
    scaleForObject(0, maxX/12 , maxY/4 * 3, maxY, type::cuttableMineral);
    scaleForObject(maxX/12, maxX/12 + 3, maxY/4 * 3, maxY,type::uncuttableMineral);
    scaleForObject(maxX/2 -3, maxX/2 +3, maxY/2 -3, maxY/2 +3, type::centre);
    for(int i = 0;i <maxX; i++){
        for(int j = 0; j < maxY; j++){
            if(this->block[i][j]->type == type::centre){
                this->block[i][j] = new class centre;
            }
        }
    }
    this->isMapUpgrade = true;
    this->isCentreUpgrade = false;
}
//
void playScene::levelInit(){
    if(this->mapUpgradeTimes == 0){
        this->leveltype = levelType::level1;
        this->level1();
        qDebug() << "level1init";
    }
    qDebug() << "levelinit";
}

void playScene::mousePressEvent(QMouseEvent * event){
    //qDebug() << QCursor::pos().x() << ":" << QCursor::pos().y();
    int curx = this->mapFromGlobal(QCursor().pos()).x() / gridSize;
    int cury = this->mapFromGlobal(QCursor().pos()).y() /gridSize;
    this->cursor->pos.pos_x = curx;
    this->cursor->pos.pos_y = cury;
    //qDebug() << curx << ":" << cury;
    if(event->button() == Qt::LeftButton){
        //
        if(this->block[curx][cury]->type != type::centre&&
            (this->block[curx][cury]->devicetype == devicetype::Null||this->block[curx][cury]->devicetype == devicetype::cutternext)){
            //
            if(this->cursor->obj->devicetype == devicetype::miner){
                auto currentMiner = dynamic_cast<class miner*>(this->cursor->obj);
                //this->block[curx][cury]->devicetype = devicetype::miner;
                if(this->block[curx][cury]->type == type::cuttableMineral){
                    this->block[curx][cury] = new class miner(currentMiner->dir);
                    this->block[curx][cury]->type = type::cuttableMineral;
                    auto curminer= dynamic_cast<class miner*>(this->block[curx][cury]);
                    curminer->mineral->type = type::cuttableMineral;
                }
                else if(this->block[curx][cury]->type == type::uncuttableMineral){
                    this->block[curx][cury] = new class miner(currentMiner->dir);
                    this->block[curx][cury]->type = type::uncuttableMineral;
                    auto curminer= dynamic_cast<class miner*>(this->block[curx][cury]);
                    curminer->mineral->type = type::uncuttableMineral;
                }
                else{
                    this->block[curx][cury] = new class miner(currentMiner->dir);
                    this->block[curx][cury]->type = type::NullMineral;
                }
                //this->block[curx][cury]->dir = currentMiner->dir;
                //this->block[curx][cury] = currentMiner;
                //currentMiner->mine(this->block[curx][cury]);
                //qDebug() << currentMiner->dir ;
                this->update();
            }
            //
            else if(this->cursor->obj->devicetype == devicetype::cutter){

                auto currentCutter = dynamic_cast<class cutter*>(this->cursor->obj);

                if(currentCutter->dir == direction::up){
                    if(curx == maxX - 1){
                        return;
                    }
                    if(block[curx + 1][cury]->devicetype == devicetype::cutter||block[curx + 1][cury]->devicetype == devicetype::cutternext
                        ||block[curx][cury]->devicetype == devicetype::cutternext){
                        return;
                    }
                    else{
                        //this->block[curx][cury]->devicetype = devicetype::cutter;

                        if(this->block[curx][cury]->type == type::cuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::up);
                            this->block[curx + 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::cuttableMineral;
                        }
                        else if(this->block[curx][cury]->type == type::uncuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::up);
                            this->block[curx + 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::uncuttableMineral;
                        }
                        else{
                            this->block[curx][cury] = new class cutter(direction::up);
                            this->block[curx + 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::NullMineral;
                        }

                    }
                }
                else if(currentCutter->dir == direction::right){
                    if(cury == maxY - 1){
                        return;
                    }
                    if(block[curx][cury+1]->devicetype == devicetype::cutter||block[curx][cury+1]->devicetype == devicetype::cutternext
                        ||block[curx][cury]->devicetype == devicetype::cutternext){
                        return;
                    }
                    else{
                        //this->block[curx][cury]->devicetype = devicetype::cutter;
                        if(this->block[curx][cury]->type == type::cuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::right);
                            this->block[curx][cury+1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::cuttableMineral;
                        }
                        else if(this->block[curx][cury]->type == type::uncuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::right);
                            this->block[curx][cury+1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::uncuttableMineral;
                        }
                        else{
                            this->block[curx][cury] = new class cutter(direction::right);
                            this->block[curx][cury+1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::NullMineral;
                        }
                    }
                }
                else if(currentCutter->dir == direction::down){
                    if(curx == 0){
                        return;
                    }
                    if(block[curx - 1][cury]->devicetype == devicetype::cutter||block[curx - 1][cury]->devicetype == devicetype::cutternext
                        ||block[curx][cury]->devicetype == devicetype::cutternext){
                        return;
                    }
                    else{
                        //this->block[curx][cury]->devicetype = devicetype::cutter;
                        if(this->block[curx][cury]->type == type::cuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::down);
                            this->block[curx - 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::cuttableMineral;
                        }
                        else if(this->block[curx][cury]->type == type::uncuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::down);
                            this->block[curx - 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::uncuttableMineral;
                        }
                        else{
                            this->block[curx][cury] = new class cutter(direction::down);
                            this->block[curx - 1][cury]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::NullMineral;
                        }

                    }
                }
                else if(currentCutter->dir == direction::left){
                    if(cury == 0){
                        return;
                    }
                    if(block[curx][cury-1]->devicetype == devicetype::cutter||block[curx][cury-1]->devicetype == devicetype::cutternext
                        ||block[curx][cury]->devicetype == devicetype::cutternext){
                        return;
                    }
                    else{
                        //this->block[curx][cury]->devicetype = devicetype::cutter;
                        if(this->block[curx][cury]->type == type::cuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::left);
                            this->block[curx][cury-1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::cuttableMineral;
                        }
                        else if(this->block[curx][cury]->type == type::uncuttableMineral){
                            this->block[curx][cury] = new class cutter(direction::left);
                            this->block[curx][cury-1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::uncuttableMineral;
                        }
                        else{
                            this->block[curx][cury] = new class cutter(direction::left);
                            this->block[curx][cury-1]->devicetype = devicetype::cutternext;
                            this->block[curx][cury]->type = type::NullMineral;
                        }

                    }
                }
                //this->block[curx][cury]->dir = currentCutter->dir;
                //currentCutter = new class cutter();
                //this->block[curx][cury] = currentCutter;
                this->update();
            }
            else if(this->cursor->obj->devicetype == devicetype::conveyor){
                //this->block[curx][cury]->devicetype = devicetype::conveyor;
                auto currentconveyor = dynamic_cast<class conveyor*>(this->cursor->obj);

                //this->block[curx][cury]->dir = currentconveyor->dir;
                if(this->block[curx][cury]->type == type::cuttableMineral){
                    this->block[curx][cury] = new class conveyor(currentconveyor->dir);
                    this->block[curx][cury]->type = type::cuttableMineral;
                }
                else if(this->block[curx][cury]->type == type::uncuttableMineral){
                    this->block[curx][cury] = new class conveyor(currentconveyor->dir);
                    this->block[curx][cury]->type = type::uncuttableMineral;
                }
                else{
                    this->block[curx][cury] = new class conveyor(currentconveyor->dir);
                    this->block[curx][cury]->type = type::NullMineral;
                }
                //this->block[curx][cury]->mineraltype = mineralOnConveyor::cuttableMineralsmall;

                this->update();

            }
            else if(this->cursor->obj->devicetype == devicetype::trashbin){
                //this->block[curx][cury]->devicetype = devicetype::trashbin;
                //auto currentTrashbin = dynamic_cast<class trashbin*>(this->cursor->obj);
                if(this->block[curx][cury]->type == type::cuttableMineral){
                    this->block[curx][cury] = new class trashbin();
                    this->block[curx][cury]->type = type::cuttableMineral;
                }
                else if(this->block[curx][cury]->type == type::uncuttableMineral){
                    this->block[curx][cury] = new class trashbin();
                    this->block[curx][cury]->type = type::uncuttableMineral;
                }
                else{
                    this->block[curx][cury] = new class trashbin();
                    this->block[curx][cury]->type = type::NullMineral;
                }
                //currentTrashbin = new class trashbin();
                //this->block[curx][cury] = currentTrashbin;
                this->update();
            }
            else if(this->cursor->obj->devicetype == devicetype::transition){
                auto currentTransition = dynamic_cast<class transition*>(this->cursor->obj);
                if(this->block[curx][cury]->type == type::cuttableMineral){
                    this->block[curx][cury] = new class transition(currentTransition->dir);
                    this->block[curx][cury]->type = type::cuttableMineral;
                }
                else if(this->block[curx][cury]->type == type::uncuttableMineral){
                    this->block[curx][cury] = new class transition(currentTransition->dir);
                    this->block[curx][cury]->type = type::uncuttableMineral;
                }
                else{
                    this->block[curx][cury] = new class transition(currentTransition->dir);
                    this->block[curx][cury]->type = type::NullMineral;
                }
                //qDebug() << currentMiner->dir ;
                this->update();
            }
        }
        else{
            this->update();
        }
        //
        //this->totaloperate();
        //
    }
    //
    if (event->button() == Qt::RightButton) {
        //
        if(this->block[curx][cury]->devicetype != devicetype::cutternext){
        if(this->block[curx][cury]->type == type::cuttableMineral&&this->block[curx][cury]->devicetype != devicetype::Null){
            delete this->block[curx][cury];
            this->block[curx][cury] = new class cuttableMineral();
            this->update();
        }
        //
        else if(this->block[curx][cury]->type == type::uncuttableMineral&&this->block[curx][cury]->devicetype != devicetype::Null){
            delete this->block[curx][cury];
            this->block[curx][cury] = new class uncuttableMineral();
            this->update();
        }
        else if (this->block[curx][cury]->devicetype != devicetype::Null) {

            delete this->block[curx][cury];
            this->block[curx][cury] = new class NullMineral();
            this->update();
        }}
        if(this->block[curx][cury]->devicetype == devicetype::cutternext){
            this->block[curx][cury]->devicetype = devicetype::Null;
        }
    }
}

//change device direction
void playScene::keyPressEvent(QKeyEvent *event){
    //int curx = this->mapFromGlobal(QCursor().pos()).x() / gridSize;
    //int cury = this->mapFromGlobal(QCursor().pos()).y() /gridSize;
    //
    if(event->key() == Qt::Key_R){

        if(this->cursor->obj->devicetype == Null){
            return;
        }
        /*
        if(this->block[curx][cury]->devicetype == NULL){
            return;
        }
        */
        direction dir = direction::up;
        auto currentmachine = dynamic_cast<class machine*>(this->cursor->obj);
        //auto currentmachine = dynamic_cast<class machine*>(this->block[curx][cury]);

        if(currentmachine->dir == direction::up){
            dir = direction::right;
        }else if(currentmachine->dir == direction::right){
            dir = direction::down;
        }else if(currentmachine->dir == direction::down){
            dir = direction::left;
        }else if(currentmachine->dir == direction::left){
            dir = direction::up;
        }else if(currentmachine->dir == direction::downtoleft){
            dir = direction::lefttoup;
        }else if(currentmachine->dir == direction::lefttoup){
            dir = direction::uptoright;
        }else if(currentmachine->dir == direction::uptoright){
            dir = direction::righttodown;
        }else if(currentmachine->dir == direction::righttodown){
            dir = direction::downtoleft;
        }else if(currentmachine->dir == direction::downtoright){
            dir = direction::lefttodown;
        }else if(currentmachine->dir == direction::lefttodown){
            dir = direction::uptoleft;
        }else if(currentmachine->dir == direction::uptoleft){
            dir = direction::righttoup;
        }else if(currentmachine->dir == direction::righttoup){
            dir = direction::downtoright;
        }
        currentmachine->changeDirection(dir);


    }

    if(event->key() == Qt::Key_T){
        if(this->cursor->obj->devicetype == Null){
            return;
        }

        direction dir = direction::up;
        auto currentmachine = dynamic_cast<class machine*>(this->cursor->obj);
        //auto currentmachine = dynamic_cast<class machine*>(this->block[curx][cury]);

        if(currentmachine->dir == direction::up){
            dir = direction::uptoright;
        }else if(currentmachine->dir == direction::right){
            dir = direction::righttodown;
        }else if(currentmachine->dir == direction::down){
            dir = direction::downtoleft;
        }else if(currentmachine->dir == direction::left){
            dir = direction::lefttoup;
        }
        currentmachine->changeDirection(dir);
    }

    if(event->key() == Qt::Key_F){
        if(this->cursor->obj->devicetype == Null){
            return;
        }

        direction dir = direction::up;
        auto currentmachine = dynamic_cast<class machine*>(this->cursor->obj);
        //auto currentmachine = dynamic_cast<class machine*>(this->block[curx][cury]);

        if(currentmachine->dir == direction::up){
            dir = direction::uptoleft;
        }else if(currentmachine->dir == direction::right){
            dir = direction::righttoup;
        }else if(currentmachine->dir == direction::down){
            dir = direction::downtoright;
        }else if(currentmachine->dir == direction::left){
            dir = direction::lefttodown;
        }
        currentmachine->changeDirection(dir);
    }
}

//operate
void playScene::mineroperate(int x, int y){
    if(this->block[x][y]->devicetype != devicetype::miner){
        return;
    }
    //qDebug() << "mineroperate";
    //进行矿物的传送工作
    auto curminer = dynamic_cast<class miner*>( this->block[x][y]);
    if(curminer->curTime>=minerinterval){
        curminer->curTime=0;

        if(curminer->mineral->type == type::NullMineral){
            return;
        }
        //qDebug() << "mineroperate called";

        if(curminer->dir == direction::up){
            if(y == 0){
                return;
            }
            if(((this->block[x][y - 1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y - 1]->dir == direction::up||this->block[x][y - 1]->dir == direction::uptoleft||
                    this->block[x][y - 1]->dir == direction::uptoright)))||
                (this->block[x][y - 1]->devicetype == devicetype::cutter&&this->block[x][y - 1]->dir == direction::up) ||
                this->block[x][y - 1]->devicetype == devicetype::trashbin){
                auto nextmachine = (machine *) this->block[x][y - 1];
                nextmachine->mineral = curminer->mineral;
            }
        }
        else if(curminer->dir == direction::down){
            if(y == maxY - 1){
                return;
            }
            if(((this->block[x][y +1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y + 1]->dir == direction::down||this->block[x][y - 1]->dir == direction::downtoleft||
                   this->block[x][y + 1]->dir == direction::downtoright)))||
                (this->block[x][y+1]->devicetype == devicetype::cutter&&this->block[x][y + 1]->dir == direction::down) ||
                this->block[x][y+1]->devicetype == devicetype::trashbin){
                auto nextmachine = (machine *) this->block[x][y+1];
                nextmachine->mineral = curminer->mineral;
            }
        }
        else if(curminer->dir == direction::left){
            if(x == 0){
                return;
            }
            if(((this->block[x - 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x-1][y]->dir == direction::left||this->block[x-1][y]->dir == direction::lefttodown||
                   this->block[x-1][y]->dir == direction::lefttoup)))||
                (this->block[x-1][y]->devicetype == devicetype::cutter&&this->block[x-1][y]->dir == direction::left) ||
                this->block[x-1][y]->devicetype == devicetype::trashbin){
                auto nextmachine = (machine *) this->block[x-1][y];
                nextmachine->mineral = curminer->mineral;
            }
        }

        else if(curminer->dir == direction::right){
            if(x == maxX-1){
                return;
            }
            if(((this->block[x + 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x+1][y]->dir == direction::right||this->block[x+1][y]->dir == direction::righttodown||
                   this->block[x+1][y]->dir == direction::righttoup)))||
                (this->block[x+1][y]->devicetype == devicetype::cutter&&this->block[x+1][y]->dir == direction::right) ||
                this->block[x+1][y]->devicetype == devicetype::trashbin){
                auto nextmachine = (machine *) this->block[x+1][y];
                nextmachine->mineral = curminer->mineral;
            }
        }
        if(curminer->mineral->type == type::cuttableMineral){
            curminer->mineral = new class cuttableMineral();
        }
        if(curminer->mineral->type == type::uncuttableMineral){
            curminer->mineral = new class uncuttableMineral();
        }


    }
}

void playScene::conveyoroperate(int x, int y){
    if(this->block[x][y]->devicetype != devicetype::conveyor){
        return;
    }

    auto curconveyor = dynamic_cast<class conveyor*>( this->block[x][y]);
    //在传送带上显示出来
    if(curconveyor->mineral->type == type::cuttableMineral){
        this->block[x][y]->mineraltype = mineralOnConveyor::cuttableMineralsmall;
    }
    if(curconveyor->mineral->type == type::uncuttableMineral){
        this->block[x][y]->mineraltype = mineralOnConveyor::uncuttableMineralsmall;
    }else if(curconveyor->mineral->type == type::halfCuttableMineralleft){
        this->block[x][y]->mineraltype = mineralOnConveyor::halfCuttableMineralleftsmall;
    }else if(curconveyor->mineral->type == type::halfCuttableMineralright){
        this->block[x][y]->mineraltype = mineralOnConveyor::halfCuttableMineralrightsmall;
    }
    //if(curconveyor->curTime >= 3){
    if(curconveyor->curTime>=conveyorinterval){
        curconveyor->curTime = 0;
        if(curconveyor->mineral->type==type::NullMineral){
            return;
        }
        if(curconveyor->dir == direction::up||curconveyor->dir == direction::lefttoup||curconveyor->dir == direction::righttoup){
            if(y == 0){
                return;
            }
            if(((this->block[x][y - 1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y - 1]->dir == direction::up||this->block[x][y - 1]->dir == direction::uptoleft||
                   this->block[x][y - 1]->dir == direction::uptoright)))||
                (this->block[x][y - 1]->devicetype == devicetype::cutter&&this->block[x][y - 1]->dir == direction::up) ||
                this->block[x][y - 1]->devicetype == devicetype::trashbin||
                (this->block[x][y - 1]->devicetype == devicetype::transition&&this->block[x][y - 1]->dir == direction::up)||
                this->block[x][y - 1]->type == type::centre){
                auto nextmachine = (machine *) this->block[x][y - 1];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }

                nextmachine->mineral = curconveyor->mineral;

                curconveyor->mineral = new class NullMineral();
                this->block[x][y]->mineraltype = mineralOnConveyor::NullMineralon;
            }

        }
        else if(curconveyor->dir == direction::down||curconveyor->dir == direction::lefttodown||curconveyor->dir == direction::righttodown){
            if(y == maxY -1){
                return;
            }
            if(((this->block[x][y +1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y + 1]->dir == direction::down||this->block[x][y + 1]->dir == direction::downtoleft||
                   this->block[x][y + 1]->dir == direction::downtoright)))||
                (this->block[x][y + 1]->devicetype == devicetype::cutter&&this->block[x][y + 1]->dir == direction::down) ||
                this->block[x][y + 1]->devicetype == devicetype::trashbin||
                (this->block[x][y + 1]->devicetype == devicetype::transition&&this->block[x][y + 1]->dir == direction::down) ||
                this->block[x][y + 1]->type == type::centre){
                auto nextmachine = (machine *) this->block[x][y + 1];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }

                nextmachine->mineral = curconveyor->mineral;

                curconveyor->mineral = new class NullMineral();
                this->block[x][y]->mineraltype = mineralOnConveyor::NullMineralon;
            }

        }
        else if(curconveyor->dir == direction::left||curconveyor->dir == direction::uptoleft||curconveyor->dir == direction::downtoleft){
            if(x == 0){
                return;
            }
            if(((this->block[x - 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x-1][y]->dir == direction::left||this->block[x-1][y]->dir == direction::lefttodown||
                   this->block[x-1][y]->dir == direction::lefttoup)))||
                (this->block[x - 1][y]->devicetype == devicetype::cutter&&this->block[x-1][y]->dir == direction::left) ||
                this->block[x - 1][y]->devicetype == devicetype::trashbin||
                (this->block[x - 1][y]->devicetype == devicetype::transition&&this->block[x-1][y]->dir == direction::left)||
                this->block[x - 1][y]->type == type::centre){
                auto nextmachine = (machine *) this->block[x - 1][y];


                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }

                nextmachine->mineral = curconveyor->mineral;

                curconveyor->mineral = new class NullMineral();
                this->block[x][y]->mineraltype = mineralOnConveyor::NullMineralon;
            }

        }
        else if(curconveyor->dir == direction::right||curconveyor->dir == direction::uptoright||curconveyor->dir == direction::downtoright){
            if(x == maxX - 1){
                return;
            }
            if(((this->block[x + 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x+1][y]->dir == direction::right||this->block[x+1][y]->dir == direction::righttodown||
                   this->block[x+1][y]->dir == direction::righttoup)))||
                (this->block[x + 1][y]->devicetype == devicetype::cutter&&this->block[x+1][y]->dir == direction::right) ||
                this->block[x + 1][y]->devicetype == devicetype::trashbin||
                (this->block[x + 1][y]->devicetype == devicetype::transition&&this->block[x+1][y]->dir == direction::right) ||
                this->block[x + 1][y]->type == type::centre){
                auto nextmachine = (machine *) this->block[x + 1][y];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }
                nextmachine->mineral = curconveyor->mineral;

                curconveyor->mineral = new class NullMineral();
                this->block[x][y]->mineraltype = mineralOnConveyor::NullMineralon;
            }

        }

    }
}

void playScene::cutteroperate(int x, int y){
    if(this->block[x][y]->devicetype != devicetype::cutter){
        return;
    }

    auto curcutter = dynamic_cast<class cutter*>( this->block[x][y]);
    if(curcutter->curTime >= cutterinterval){
        curcutter->curTime = 0;
        if(curcutter->mineral->type == type::NullMineral){
            return;
        }
        auto curMineral = dynamic_cast<class Mineral*>(curcutter->mineral);
        if(curMineral->isCuttable){
            qDebug() << "Cutter cuts the mineral";
            if(curcutter->dir == direction::up){
                if(y == 0){
                    return;
                }
                if( ((this->block[x][y - 1]->devicetype == devicetype::conveyor &&
                    (this->block[x][y - 1]->dir == direction::up||this->block[x][y - 1]->dir == direction::uptoleft||
                     this->block[x][y - 1]->dir == direction::uptoright))||
                     (this->block[x][y - 1]->devicetype == devicetype::cutter&&this->block[x][y - 1]->dir == direction::up) ||
                     (this->block[x][y - 1]->devicetype == devicetype::transition&&this->block[x][y - 1]->dir == direction::up)||
                    this->block[x][y - 1]->devicetype == devicetype::trashbin )
                    &&
                    ((this->block[x + 1][y - 1]->devicetype == devicetype::conveyor &&
                    (this->block[x+ 1][y - 1]->dir == direction::up||this->block[x][y - 1]->dir == direction::uptoleft||
                    this->block[x+ 1][y - 1]->dir == direction::uptoright))||
                    (this->block[x + 1][y - 1]->devicetype == devicetype::cutter&&this->block[x+1][y - 1]->dir == direction::up)||
                    (this->block[x + 1][y - 1]->devicetype == devicetype::transition&&this->block[x+1][y - 1]->dir == direction::up)||
                    this->block[x + 1][y - 1]->devicetype == devicetype::trashbin))
                    {
                    auto nextmachine1 = dynamic_cast<class machine*>(this->block[x][y-1]);
                    auto nextmachine2 = dynamic_cast<class machine*>(this->block[x+1][y-1]);
                    if(nextmachine1->mineral->type != type::NullMineral ||nextmachine2->mineral->type != type::NullMineral){
                        return;
                    }

                    free(curcutter->mineral);
                    curcutter->mineral = new class NullMineral();
                    nextmachine1->mineral = new class halfCuttableMineralleft();
                    nextmachine2->mineral = new class halfCuttableMineralright();

                }
            }
            else if(curcutter->dir == direction::down){
                if(y == maxY - 1){
                    return;
                }
                if( ((this->block[x][y + 1]->devicetype == devicetype::conveyor &&
                      (this->block[x][y + 1]->dir == direction::down||this->block[x][y + 1]->dir == direction::downtoleft||
                       this->block[x][y + 1]->dir == direction::downtoright))||
                     (this->block[x][y + 1]->devicetype == devicetype::cutter&&this->block[x][y + 1]->dir == direction::down) ||
                     (this->block[x][y + 1]->devicetype == devicetype::transition&&this->block[x][y + 1]->dir == direction::down) ||
                     this->block[x][y + 1]->devicetype == devicetype::trashbin )
                    &&
                    ((this->block[x - 1][y + 1]->devicetype == devicetype::conveyor &&
                      (this->block[x- 1][y + 1]->dir == direction::down||this->block[x-1][y + 1]->dir == direction::downtoleft||
                       this->block[x- 1][y + 1]->dir == direction::downtoright))||
                     (this->block[x - 1][y + 1]->devicetype == devicetype::cutter&&this->block[x - 1][y + 1]->dir == direction::down)||
                     (this->block[x - 1][y + 1]->devicetype == devicetype::transition&&this->block[x - 1][y + 1]->dir == direction::down)||
                     this->block[x - 1][y + 1]->devicetype == devicetype::trashbin))
                {
                    auto nextmachine1 = dynamic_cast<class machine*>(this->block[x][y+1]);
                    auto nextmachine2 = dynamic_cast<class machine*>(this->block[x-1][y+1]);
                    if(nextmachine1->mineral->type != type::NullMineral ||nextmachine2->mineral->type != type::NullMineral){
                        return;
                    }

                    free(curcutter->mineral);
                    curcutter->mineral = new class NullMineral();
                    nextmachine1->mineral = new class halfCuttableMineralleft();
                    nextmachine2->mineral = new class halfCuttableMineralright();

                }

            }else if(curcutter->dir == direction::left){
                if(x == 0){
                    return;
                }
                if( ((this->block[x -1][y - 1]->devicetype == devicetype::conveyor &&
                      (this->block[x-1][y - 1]->dir == direction::left||this->block[x-1][y - 1]->dir == direction::lefttoup||
                       this->block[x-1][y - 1]->dir == direction::lefttodown))||
                     (this->block[x-1][y - 1]->devicetype == devicetype::cutter&&this->block[x-1][y - 1]->dir == direction::left) ||
                      (this->block[x-1][y - 1]->devicetype == devicetype::transition&&this->block[x-1][y - 1]->dir == direction::left) ||
                     this->block[x-1][y - 1]->devicetype == devicetype::trashbin )
                    &&
                    ((this->block[x - 1][y ]->devicetype == devicetype::conveyor &&
                      (this->block[x- 1][y ]->dir == direction::left||this->block[x-1][y]->dir == direction::lefttoup||
                       this->block[x- 1][y ]->dir == direction::lefttodown))||
                     (this->block[x - 1][y]->devicetype == devicetype::cutter&&this->block[x- 1][y ]->dir == direction::left)||
                     (this->block[x - 1][y]->devicetype == devicetype::transition&&this->block[x- 1][y ]->dir == direction::left)||
                     this->block[x - 1][y ]->devicetype == devicetype::trashbin))
                {
                    auto nextmachine1 = dynamic_cast<class machine*>(this->block[x-1][y]);
                    auto nextmachine2 = dynamic_cast<class machine*>(this->block[x-1][y-1]);
                    if(nextmachine1->mineral->type != type::NullMineral ||nextmachine2->mineral->type != type::NullMineral){
                        return;
                    }

                    free(curcutter->mineral);
                    curcutter->mineral = new class NullMineral();
                    nextmachine1->mineral = new class halfCuttableMineralleft();
                    nextmachine2->mineral = new class halfCuttableMineralright();

                }
            }else if(curcutter->dir == direction::right){
                qDebug() << "curcutter right called";
                if(x == maxX -1){
                    return;
                }
                if( ((this->block[x+1][y]->devicetype == devicetype::conveyor &&
                      (this->block[x+1][y]->dir == direction::right||this->block[x+1][y]->dir == direction::righttoup||
                       this->block[x+1][y]->dir == direction::righttodown))||
                     (this->block[x+1][y]->devicetype == devicetype::cutter&&this->block[x+1][y]->dir == direction::right) ||
                     (this->block[x+1][y]->devicetype == devicetype::transition&&this->block[x+1][y]->dir == direction::right) ||
                     this->block[x+1][y ]->devicetype == devicetype::trashbin )
                    &&
                    ((this->block[x + 1][y+1]->devicetype == devicetype::conveyor &&
                      (this->block[x+ 1][y+1]->dir == direction::right||this->block[x+1][y + 1]->dir == direction::righttoup||
                       this->block[x+ 1][y+1]->dir == direction::righttodown))||
                     (this->block[x + 1][y + 1]->devicetype == devicetype::cutter&&this->block[x+ 1][y+1]->dir == direction::right)||
                     (this->block[x + 1][y + 1]->devicetype == devicetype::transition&&this->block[x+ 1][y+1]->dir == direction::right)||
                     this->block[x + 1][y + 1]->devicetype == devicetype::trashbin))
                {
                    auto nextmachine1 = dynamic_cast<class machine*>(this->block[x+1][y]);
                    auto nextmachine2 = dynamic_cast<class machine*>(this->block[x+1][y+1]);
                    if(nextmachine1->mineral->type != type::NullMineral ||nextmachine2->mineral->type != type::NullMineral){
                        //qDebug() << "curcutter right return ";
                        return;
                    }
                    //qDebug() << "curcutter right have called ";
                    qDebug() << "Cutter cuts " << curcutter->mineral->type;
                    free(curcutter->mineral);

                    curcutter->mineral = new class NullMineral();
                    qDebug() << "Cutter cuts " << curcutter->mineral;
                    nextmachine1->mineral = new class halfCuttableMineralleft();
                    nextmachine2->mineral = new class halfCuttableMineralright();

                }
            }
        }
    }
}

void playScene::trashbinoperate(int x, int y){
    if(this->block[x][y]->devicetype != devicetype::trashbin){
        return;
    }    
    auto curtrashbin = dynamic_cast<class trashbin*>( this->block[x][y]);
    if(curtrashbin->curTime >= 0){
        curtrashbin->curTime = 0;
        if(curtrashbin->mineral && curtrashbin->mineral->type == type::NullMineral){
            return;
        }
        delete(curtrashbin->mineral);
        curtrashbin->mineral = new class NullMineral();
    }
}

void playScene::transitionoperate(int x, int y){
    if(this->block[x][y]->devicetype != devicetype::transition){
        return;
    }
    auto curtransition = dynamic_cast<class transition*>( this->block[x][y]);
    if(curtransition->curTime >= transitioninterval){
        curtransition->curTime = 0;
        if(curtransition->mineral->type == type::NullMineral){
            return;
        }
        if(curtransition->dir == direction::up){
            if(y == 0){
                return;
            }
            if(((this->block[x][y - 1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y - 1]->dir == direction::up||this->block[x][y - 1]->dir == direction::uptoleft||
                   this->block[x][y - 1]->dir == direction::uptoright)))||
                (this->block[x][y - 1]->devicetype == devicetype::cutter&&this->block[x][y - 1]->dir == direction::up) ||
                this->block[x][y - 1]->devicetype == devicetype::trashbin||
                (this->block[x][y - 1]->devicetype == devicetype::transition&&this->block[x][y - 1]->dir == direction::up)||
                this->block[x][y - 1]->type == type::centre){
                auto nextmachine = (machine *) this->block[x][y - 1];
                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }
                if(curtransition->mineral->type == type::halfCuttableMineralleft)
                {   nextmachine->mineral = new class halfCuttableMineralright;
                    curtransition->mineral=new class NullMineral;
                }
                else if(curtransition->mineral->type == type::halfCuttableMineralright)
                {   nextmachine->mineral = new class halfCuttableMineralleft;
                    curtransition->mineral=new class NullMineral;
                }
                else{
                    nextmachine->mineral = curtransition->mineral;
                    curtransition->mineral=new class NullMineral;
                }
            }
        }
        else if(curtransition->dir == direction::down){
            if(y == maxY -1){
                return;
            }
            if(((this->block[x][y +1]->devicetype == devicetype::conveyor &&
                  (this->block[x][y + 1]->dir == direction::down||this->block[x][y + 1]->dir == direction::downtoleft||
                   this->block[x][y + 1]->dir == direction::downtoright)))||
                (this->block[x][y + 1]->devicetype == devicetype::cutter&&this->block[x][y + 1]->dir == direction::down) ||
                this->block[x][y + 1]->devicetype == devicetype::trashbin||
                (this->block[x][y + 1]->devicetype == devicetype::transition&&this->block[x][y + 1]->dir == direction::down) ||
                this->block[x][y + 1]->type == type::centre){
                auto nextmachine = (machine *) this->block[x][y + 1];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }
                if(curtransition->mineral->type == type::halfCuttableMineralleft)
                {   nextmachine->mineral = new class halfCuttableMineralright;
                    curtransition->mineral=new class NullMineral;
                }
                else if(curtransition->mineral->type == type::halfCuttableMineralright)
                {   nextmachine->mineral = new class halfCuttableMineralleft;
                    curtransition->mineral=new class NullMineral;
                }
                else{
                    nextmachine->mineral = curtransition->mineral;
                    curtransition->mineral=new class NullMineral;
                }

            }

        }
        else if(curtransition->dir == direction::left){
            if(x == 0){
                return;
            }
            if(((this->block[x - 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x-1][y]->dir == direction::left||this->block[x-1][y]->dir == direction::lefttodown||
                   this->block[x-1][y]->dir == direction::lefttoup)))||
                (this->block[x - 1][y]->devicetype == devicetype::cutter&&this->block[x-1][y]->dir == direction::left) ||
                this->block[x - 1][y]->devicetype == devicetype::trashbin||
                (this->block[x - 1][y]->devicetype == devicetype::transition&&this->block[x-1][y]->dir == direction::left)||
                this->block[x - 1][y]->type == type::centre){
                auto nextmachine = (machine *) this->block[x - 1][y];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }
                if(curtransition->mineral->type == type::halfCuttableMineralleft)
                {   nextmachine->mineral = new class halfCuttableMineralright;
                    curtransition->mineral=new class NullMineral;
                }
                else if(curtransition->mineral->type == type::halfCuttableMineralright)
                {   nextmachine->mineral = new class halfCuttableMineralleft;
                    curtransition->mineral=new class NullMineral;
                }
                else{
                    nextmachine->mineral = curtransition->mineral;
                    curtransition->mineral=new class NullMineral;
                }

            }

        }
        else if(curtransition->dir == direction::right){
            if(x == maxX - 1){
                return;
            }
            if(((this->block[x + 1][y]->devicetype == devicetype::conveyor &&
                  (this->block[x+1][y]->dir == direction::right||this->block[x+1][y]->dir == direction::righttodown||
                   this->block[x+1][y]->dir == direction::righttoup)))||
                (this->block[x + 1][y]->devicetype == devicetype::cutter&&this->block[x+1][y]->dir == direction::right) ||
                this->block[x + 1][y]->devicetype == devicetype::trashbin||
                (this->block[x + 1][y]->devicetype == devicetype::transition&&this->block[x+1][y]->dir == direction::right) ||
                this->block[x + 1][y]->type == type::centre){
                auto nextmachine = (machine *) this->block[x + 1][y];

                if(nextmachine->mineral->type != type::NullMineral){
                    //阻塞传送带的前进
                    return;
                }
                if(curtransition->mineral->type == type::halfCuttableMineralleft)
                {   nextmachine->mineral = new class halfCuttableMineralright;
                    curtransition->mineral=new class NullMineral;
                }
                else if(curtransition->mineral->type == type::halfCuttableMineralright)
                {   nextmachine->mineral = new class halfCuttableMineralleft;
                    curtransition->mineral=new class NullMineral;
                }
                else{
                    nextmachine->mineral = curtransition->mineral;
                    curtransition->mineral=new class NullMineral;
                }

            }

        }
    }
}

void playScene::updatetime(int x, int y){
    if (this->block[x][y]->devicetype == devicetype::miner ||
        this->block[x][y]->devicetype == devicetype::conveyor ||
        this->block[x][y]->devicetype == devicetype::cutter ||
        this->block[x][y]->devicetype == devicetype::transition||
        this->block[x][y]->devicetype == devicetype::trashbin) {
        auto curmachine = (machine *) this->block[x][y];
        curmachine->curTime++;
    }
}

void playScene::totaloperate(){
    for(int i = 0;i < maxX; i++){
        for(int j=0;j < maxY; j++){
            this->updatetime(i, j);

        }
    }
    //Transmisson(curTrans,ToDir);
    for(int i = 0;i < maxX; i++){
        for(int j=0;j < maxY; j++){
            //this->CentreOperate(i,j);
            //this->CutterOperate(i,j);

            this->mineroperate(i,j);
            this->cutteroperate(i,j);
            this->transitionoperate(i,j);
            this->trashbinoperate(i,j);
            //updateEquipmentCurTime(i,j);
            this->conveyoroperate(i,j);
            this->centreoperate(i,j);
        }
    }
    /*
    for(int i = 0;i < maxX; i++){
        for(int j=0;j < maxY; j++){

        }
    }
    */


}

//绘图事件
void playScene::paintEvent(QPaintEvent * ){

    QPainter painter(this);

    //设置画笔

    painter.setPen(Qt::gray);

    //画画
    for(int x = 0; x < GAME_WIDTH; x += gridSize){
        painter.drawLine(x, 0, x, GAME_HEIGHT);
    }
    for(int y = 0; y < GAME_HEIGHT; y += gridSize){
        painter.drawLine(0, y, GAME_WIDTH, y);
    }
    //qDebug() << "paintgrid called";
    for (int i = 0; i < maxX; i++) {
        for (int j = 0; j < maxY; j++) {
            if (block[i][j] && block[i][j]->type != type::NullMineral) {

                //qDebug() << "Block[" << i << "][" << j << "] type:" << block[i][j]->type;

                if(block[i][j]->type == type::cuttableMineral){
                    //qDebug() << "cuttableMineral";
                    //qDebug() << "cuttableMineral icon is null: " << cuttableMineral.icon.isNull();
                    painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, cuttableMineral.icon);
                    //qDebug() << "cuttableMineral called";
                }
                else if(block[i][j]->type == type::uncuttableMineral){
                    painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, uncuttableMineral.icon);
                    //qDebug() << "uncuttableMineral";
                }
                else if(block[i][j]->type == type::centre){
                    painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, centre.icon);
                    //qDebug() << "uncuttableMineral";
                }
                //


            } else {
                //qDebug() << "Block[" << i << "][" << j << "] is null or empty";
            }
            //
            if(block[i][j]->devicetype == devicetype::miner){
                painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, block[i][j]->icon);
                //qDebug() <<"paintminer" ;
            }

            else if(block[i][j]->devicetype == devicetype::cutter){

                //currentCutter = dynamic_cast<class cutter*>(this->cursor->obj);
                if(block[i][j]->dir == direction::up){
                    //currentCutter = new class cutter(direction::up, order::first);
                    painter.drawPixmap(i * gridSize, j * gridSize, gridSize * 2, gridSize, block[i][j]->icon);
                }
                else if(block[i][j]->dir == direction::right){
                    //currentCutter = new class cutter(direction::right, order::first);
                    painter.drawPixmap(i * gridSize, j * gridSize, gridSize , gridSize *2, block[i][j]->icon);
                }
                else if(block[i][j]->dir == direction::down){
                    //currentCutter = new class cutter(direction::down, order::first);
                    painter.drawPixmap(i * gridSize - gridSize, j * gridSize, gridSize * 2, gridSize, block[i][j]->icon);
                }
                else if(block[i][j]->dir == direction::left){
                    //currentCutter = new class cutter(direction::left, order::first);
                    painter.drawPixmap(i * gridSize, j * gridSize - gridSize , gridSize , gridSize *2, block[i][j]->icon);
                }
                //qDebug() <<"paintcutter" ;
            }
            //
            else if(block[i][j]->devicetype == devicetype::conveyor){
                painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, block[i][j]->icon);
                if(block[i][j]->mineraltype == mineralOnConveyor::cuttableMineralsmall){
                    painter.drawPixmap(i * gridSize+ gridSize/4, j * gridSize +gridSize/4, gridSize /2, gridSize/2, cuttableMineral.icon);
                }
                else if(block[i][j]->mineraltype == mineralOnConveyor::uncuttableMineralsmall){
                    painter.drawPixmap(i * gridSize+ gridSize/4, j * gridSize +gridSize/4, gridSize /2, gridSize/2, uncuttableMineral.icon);
                }
                else if(block[i][j]->mineraltype == mineralOnConveyor::halfCuttableMineralleftsmall){
                    painter.drawPixmap(i * gridSize+ gridSize/4, j * gridSize +gridSize/4, gridSize /4, gridSize/2, halfmineralleft.icon);
                }
                else if(block[i][j]->mineraltype == mineralOnConveyor::halfCuttableMineralrightsmall){
                    painter.drawPixmap(i * gridSize+ gridSize/4, j * gridSize +gridSize/4, gridSize /4, gridSize/2, halfmineralright.icon);
                }
                //qDebug() <<"paintconveyor" ;
            }
            //
            else if(block[i][j]->devicetype == devicetype::transition){
                painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, block[i][j]->icon);
                //qDebug() <<"paintminer" ;
            }
            else if(block[i][j]->devicetype == devicetype::trashbin){
                //currentTrashbin = new class trashbin();
                //currentTrashbin = dynamic_cast<class trashbin*>(this->cursor->obj);
                painter.drawPixmap(i * gridSize, j * gridSize, gridSize, gridSize, block[i][j]->icon);
                //qDebug() <<"painttrashbin" ;
            }
        }
    }
    //declaration.setText("点击空白即为退出游戏\n点击设备就可以开始了！\n");
    declaration.setFixedSize(400, 80);
    declaration.move(GAME_WIDTH * 4/5, 0);
    currentmoney.setText(QString("Current Money: %1").arg(scene::money));
    currentmoney.move(GAME_WIDTH * 4/5, 0);
    if(this->leveltype == levelType::level1){
        painter.drawPixmap(GAME_WIDTH * 23/24, GAME_HEIGHT /12 + 40, gridSize /2, gridSize/2, cuttableMineral.icon);
        currentmission1.setText(QString("Level 1\nMission1 请交付:\n%1/%2\n×键返回主界面").arg(cuttablemineralnum).arg(cuttablemineraltarget));
        currentmission1.setFixedHeight(140);
        currentmission1.move(GAME_WIDTH * 4/5, GAME_HEIGHT /12);
    }
    else if(this->leveltype == levelType::level2){
        painter.drawPixmap(GAME_WIDTH * 23/24, GAME_HEIGHT /12 + 40, gridSize /2, gridSize/2, uncuttableMineral.icon);
        currentmission1.setText(QString("Level 2\nMission2 请交付:\n%1/%2\n×键返回主界面").arg(uncuttablemineralnum).arg(uncuttablemineraltarget));
        currentmission1.setFixedHeight(140);
        currentmission1.move(GAME_WIDTH * 4/5, GAME_HEIGHT /12);
    }
    else if(this->leveltype == levelType::level3){
        painter.drawPixmap(GAME_WIDTH * 23/24, GAME_HEIGHT /12 + 40, gridSize /4, gridSize/2, halfmineralleft.icon);
        currentmission1.setText(QString("Level 3\nMission3 请交付:\n%1/%2\n×键返回主界面").arg(halfmineralnum).arg(halfminerallefttarget));
        currentmission1.setFixedHeight(140);
        currentmission1.move(GAME_WIDTH * 4/5, GAME_HEIGHT /12);
    }
    else if(this->leveltype == levelType::level4){
        currentmission1.setText(QString("Level 4\n×键返回主界面"));
        currentmission1.setFixedHeight(70);
        currentmission1.move(GAME_WIDTH * 4/5, GAME_HEIGHT /12);
    }
    //qDebug() << "paintEvent called";

}
//
void playScene::connections(){

}

void playScene::setTxt(QTextEdit * txt)
{
    txt->setReadOnly(true);
    txt->setParent(this);

    txt->setStyleSheet("background: transparent; color: black; border-style: outset; font: bold 25px; font-family: 微软雅黑;");
}

//some missions
//每次一个mineral进入centre，money increase, however, the target is also important.
void playScene::mission1(class centre *curcentre){

    if(curcentre->mineral->type == type::cuttableMineral){
        qDebug() << "mission1 called";
        playScene::cuttablemineralnum++;
        scene::money += cuttableMineral.value;

        delete(curcentre->mineral);
        curcentre->mineral = new class NullMineral();
    }
}

void playScene::mission2(class centre *curcentre){

    if(curcentre->mineral->type == type::uncuttableMineral){
        playScene::uncuttablemineralnum++;
        scene::money += uncuttableMineral.value;

        delete(curcentre->mineral);
        curcentre->mineral = new class NullMineral();
    }
}

void playScene::mission3(class centre *curcentre){

    if(curcentre->mineral->type == halfCuttableMineralleft){
        playScene::halfmineralnum++;
        scene::money += halfmineralleft.value;

        delete(curcentre->mineral);
        curcentre->mineral = new class NullMineral();
    }
    else if(curcentre->mineral->type == halfCuttableMineralright){
        //playScene::halfmineralnum++;
        scene::money += halfmineralright.value;

        delete(curcentre->mineral);
        curcentre->mineral = new class NullMineral();
    }
}

void playScene::missionjudge(){
    if(playScene::cuttablemineralnum >= cuttablemineraltarget&&this->leveltype == levelType::level1){
        this->ismission1 = true;
        playScene::uncuttablemineralnum = 0;
        this->leveltype = levelType::level2;

        QMessageBox congratulationsDialog;
        congratulationsDialog.setFixedSize(400, 200);
        QFont font;
        font.setPointSize(14);
        congratulationsDialog.setFont(font);
        congratulationsDialog.setText("Congratulations! You have completed mission 1.\n你现在解锁了传送带和开采器的升级，也可以对交付中心升级了");
        congratulationsDialog.exec();
        //QMessageBox::information(nullptr, "Congratulations", "You have completed mission 1.");
        this->update();
        this->ismission1 = false;
    }
    if(playScene::uncuttablemineralnum >= uncuttablemineraltarget&&this->leveltype == levelType::level2){
        this->ismission2 = true;
        playScene::halfmineralnum = 0;
        this->leveltype = levelType::level3;

        QMessageBox congratulationsDialog;
        congratulationsDialog.setFixedSize(400, 200);
        QFont font;
        font.setPointSize(14);
        congratulationsDialog.setFont(font);
        congratulationsDialog.setText("Congratulations! You have completed mission 2.\n你现在解锁了切割机和旋转器的升级");
        congratulationsDialog.exec();
        //congratulationsDialog.done(QMessageBox::Accepted);
        //QMessageBox::information(nullptr, "Congratulations", "You have completed mission 1.");
        this->update();
        this->ismission2 = false;
    }
    if(playScene::halfmineralnum >= halfminerallefttarget&&this->leveltype == levelType::level3){
        this->ismission3 = true;
        this->leveltype = levelType::level4;

        QMessageBox congratulationsDialog;
        congratulationsDialog.setFixedSize(400, 200);
        QFont font;
        font.setPointSize(14);
        congratulationsDialog.setFont(font);
        congratulationsDialog.setText("Congratulations! You have completed mission 3.\nALL MISSIONS HAVE BEEN COMPLETED!.\n"
                                      "你可以对地图升级了，升级完地图后，还可以对交付中心做进一步升级哦");
        congratulationsDialog.exec();
        //congratulationsDialog.done(QMessageBox::Accepted);
        //QMessageBox::information(nullptr, "Congratulations", "You have completed mission 1.");
        this->update();
    }
}

void playScene::centreoperate(int x,int y){
    if(this->block[x][y]->type != type::centre){
        return;
    }
    //qDebug() << "centre operate called";

    auto curcentre = dynamic_cast<class centre*>( this->block[x][y]);
    if(curcentre->curTime >= 0){
        curcentre->curTime = 0;
        this->mission1(curcentre);
        this->mission2(curcentre);
        this->mission3(curcentre);
        this->missionjudge();

    }

}
//开采器按钮
void playScene::setMinerButton()
{
    minerbutton = new myPushButton;
    minerbutton->move(2* GAME_WIDTH / 12, 11* GAME_HEIGHT / 12);
    minerbutton->setFixedSize(50, 50);
    minerbutton->setStyleSheet("QPushButton{border-image: url(:/Images/device/miner_up.png)}");
    minerbutton->setParent(this);
}

//传送带按钮
void playScene::setBeltButton()
{
    belt = new myPushButton;
    belt->move(3 * GAME_WIDTH / 12, 11* GAME_HEIGHT / 12);
    belt->setFixedSize(50, 50);
    belt->setStyleSheet("QPushButton{border-image: url(:/Images/device/conveyor_up.png)}");
    belt->setParent(this);
}

//切割机按钮
void playScene::setCutterButton()
{
    cutter = new myPushButton;
    cutter->move(4 * GAME_WIDTH / 12, 11* GAME_HEIGHT / 12);
    cutter->setFixedSize(100, 50);
    cutter->setStyleSheet("QPushButton{border-image: url(:/Images/device/cutter_up.png)}");
    cutter->setParent(this);
}

//垃圾桶按钮
void playScene::setTrashButton()
{
    trash = new myPushButton;
    trash->move( GAME_WIDTH / 2, 11* GAME_HEIGHT / 12);
    trash->setFixedSize(50, 50);
    trash->setStyleSheet("QPushButton{border-image: url(:/Images/device/trash.png)}");
    trash->setParent(this);
}

void playScene::setTransitionButton()
{
    transitionbutton = new myPushButton;
    transitionbutton->move(5* GAME_WIDTH / 12, 11* GAME_HEIGHT / 12);
    transitionbutton->setFixedSize(50, 50);
    transitionbutton->setStyleSheet("QPushButton{border-image: url(:/Images/device/transition_up.png)}");
    transitionbutton->setParent(this);
}

//升级（全局）
void playScene::setLevelUpButton()
{

    levelUp->move(7 * GAME_WIDTH / 12, 11* GAME_HEIGHT / 12);
    levelUp->setFixedSize(50, 50);
    levelUp->setStyleSheet("QPushButton{border-image: url(:/Images/button/shop.png)}");
    levelUp->setParent(this);
}

//帮助与音乐
void playScene::setHelpButton()
{

    help->move(8 * GAME_WIDTH / 12 , 11* GAME_HEIGHT / 12);
    help->setFixedSize(50, 50);
    help->setStyleSheet("QPushButton{border-image: url(:/Images/button/main_menu_settings.png)}");
    help->setParent(this);
}

#include <QProcess>

void playScene::saveGame() {
    QString fileName = "savedGame.txt";
    QFile saveFile(fileName);

    if (saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&saveFile);

        out << money << "\n";
        out << playScene::conveyorinterval<< "\n";
        out << playScene::minerinterval<< "\n";
        out << playScene::cutterinterval<< "\n";
        out << playScene::transitioninterval<< "\n";
        out << playScene::gridSize<< "\n";
        out << this->leveltype << "\n";
        out << this->mapUpgradeTimes << "\n";
        out << this->isMapUpgrade << "\n";
        out << this->isCentreUpgrade << "\n";
        out << playScene::cuttablemineralnum << "\n";
        out << playScene::uncuttablemineralnum << "\n";
        out << playScene::halfmineralnum << "\n";

        out << this->maxX << " " <<this->maxY << "\n";

        for(int i = 0; i < maxX; i++){
            for(int j = 0; j < maxY; j++){
                out << this->block[i][j]->type << " " <<this->block[i][j]->devicetype << " " <<this->block[i][j]->curTime <<
                    " " <<this->block[i][j]->dir <<"\n";
            }
        }
        saveFile.close();


        QProcess::startDetached("notepad.exe", QStringList() << fileName);
    } else {
        qDebug() << "Could not open file for writing:" << saveFile.errorString();
    }
}

void playScene::loadGame() {
    QString fileName = "savedGame.txt";
    QFile loadFile(fileName);
    //this->init();
    if (loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&loadFile);

        // Read and set game state from the file
        in >> scene::money;
        in >> playScene::conveyorinterval;
        in >> playScene::minerinterval;
        in >> playScene::cutterinterval;
        in >> playScene::transitioninterval;
        in >> playScene::gridSize;

        int leveltypeInt;
        in >> leveltypeInt;
        leveltype = static_cast<levelType>(leveltypeInt);

        in >> mapUpgradeTimes;

        QString isMapUpgradeStr;
        in >> isMapUpgradeStr;
        isMapUpgrade = (isMapUpgradeStr == "true");

        QString isCentreUpgradeStr;
        in >> isCentreUpgradeStr;
        isCentreUpgrade = (isCentreUpgradeStr == "true");

        in >> playScene::cuttablemineralnum;
        in >> playScene::uncuttablemineralnum;
        in >> playScene::halfmineralnum;

        int loadedMaxX, loadedMaxY;
        in >> loadedMaxX >> loadedMaxY;

        this->maxX = GAME_WIDTH/gridSize;
        this->maxY = GAME_HEIGHT/gridSize;

        // Read and set the state of each block
        for (int i = 0; i < maxX; i++) {
            for (int j = 0; j < maxY; j++) {
                int blockType, deviceType, curTime, dir;
                in >>blockType>> deviceType >> curTime >> dir;
                this->block[i][j]->type = static_cast<type>(blockType);
                this->block[i][j]->devicetype = static_cast<devicetype>(deviceType);
                this->block[i][j]->dir = static_cast<direction>(dir);
                if(this->block[i][j]->type == type::centre){
                    this->block[i][j] = new class centre;
                }
                if(this->block[i][j]->devicetype == devicetype::cutter){
                    if(this->block[i][j]->dir== direction::up){
                        if(i == maxX - 1){
                            return;
                        }
                        if(block[i + 1][j]->devicetype == devicetype::cutter||block[i + 1][j]->devicetype == devicetype::cutternext
                            ||block[i][j]->devicetype == devicetype::cutternext){
                            return;
                        }
                        else{
                            //this->block[curx][cury]->devicetype = devicetype::cutter;

                            if(this->block[i][j]->type == type::cuttableMineral){
                                this->block[i][j] = new class cutter(direction::up);
                                this->block[i+1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::cuttableMineral;

                            }
                            else if(this->block[i][j]->type == type::uncuttableMineral){
                                this->block[i][j] = new class cutter(direction::up);
                                this->block[i+1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::uncuttableMineral;
                            }
                            else{
                                this->block[i][j] = new class cutter(direction::up);
                                this->block[i+1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::NullMineral;
                            }

                        }
                    }
                    else if(this->block[i][j]->dir == direction::right){
                        if(j == maxY - 1){
                            return;
                        }
                        if(this->block[i][j+1]->devicetype == devicetype::cutter||this->block[i][j+1]->devicetype == devicetype::cutternext
                            ||this->block[i][j]->devicetype == devicetype::cutternext){
                            return;
                        }
                        else{
                            //this->block[curx][cury]->devicetype = devicetype::cutter;
                            if(this->block[i][j]->type == type::cuttableMineral){
                                this->block[i][j] = new class cutter(direction::right);
                                this->block[i][j+1]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::cuttableMineral;
                            }
                            else if(this->block[i][j]->type == type::uncuttableMineral){
                                this->block[i][j+1] = new class cutter(direction::right);
                                this->block[i][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::uncuttableMineral;
                            }
                            else{
                                this->block[i][j] = new class cutter(direction::right);
                                this->block[i][j+1]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::NullMineral;
                            }
                        }
                    }
                    else if(this->block[i][j]->dir == direction::down){
                        if(i == 0){
                            return;
                        }
                        if(this->block[i-1][j]->devicetype == devicetype::cutter||this->block[i-1][j]->devicetype == devicetype::cutternext
                            ||this->block[i][j]->devicetype == devicetype::cutternext){
                            return;
                        }
                        else{
                            //this->block[curx][cury]->devicetype = devicetype::cutter;
                            if(this->block[i][j]->type == type::cuttableMineral){
                                this->block[i][j] = new class cutter(direction::down);
                                this->block[i-1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::cuttableMineral;
                            }
                            else if(this->block[i][j]->type == type::uncuttableMineral){
                                this->block[i][j] = new class cutter(direction::down);
                                this->block[i-1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::uncuttableMineral;
                            }
                            else{
                                this->block[i][j] = new class cutter(direction::down);
                                this->block[i-1][j]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::NullMineral;
                            }

                        }
                    }
                    else if(this->block[i][j]->dir == direction::left){
                        if(j == 0){
                            return;
                        }
                        if(this->block[i][j-1]->devicetype == devicetype::cutter||this->block[i][j-1]->devicetype == devicetype::cutternext
                            ||this->block[i][j]->devicetype == devicetype::cutternext){
                            return;
                        }
                        else{
                            //this->block[curx][cury]->devicetype = devicetype::cutter;
                            if(this->block[i][j]->type == type::cuttableMineral){
                                this->block[i][j] = new class cutter(direction::left);
                                this->block[i][j-1]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::cuttableMineral;
                            }
                            else if(this->block[i][j]->type == type::uncuttableMineral){
                                this->block[i][j] = new class cutter(direction::left);
                                this->block[i][j-1]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::uncuttableMineral;
                            }
                            else{
                                this->block[i][j] = new class cutter(direction::left);
                                this->block[i][j-1]->devicetype = devicetype::cutternext;
                                this->block[i][j]->type = type::NullMineral;
                            }

                        }
                    }

                }
                if(this->block[i][j]->devicetype == devicetype::conveyor){
                    if(this->block[i][j]->type == type::cuttableMineral){
                        this->block[i][j] = new class conveyor(this->block[i][j]->dir);
                        this->block[i][j]->type = type::cuttableMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                    else if(this->block[i][j]->type == type::uncuttableMineral){
                        this->block[i][j] = new class conveyor(this->block[i][j]->dir);
                        this->block[i][j]->type = type::uncuttableMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                    else{
                        this->block[i][j] = new class conveyor(this->block[i][j]->dir);
                        this->block[i][j]->type = type::NullMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                    this->block[i][j]->mineraltype = mineralOnConveyor::NullMineralon;

                }
                else if(this->block[i][j]->devicetype == devicetype::miner){
                    if(this->block[i][j]->type == type::cuttableMineral){
                        this->block[i][j] = new class miner(this->block[i][j]->dir);
                        this->block[i][j]->type = type::cuttableMineral;
                        this->block[i][j]->curTime = curTime;
                        auto curminer= dynamic_cast<class miner*>(this->block[i][j]);
                        curminer->mineral->type = type::cuttableMineral;
                    }
                    else if(this->block[i][j]->type == type::uncuttableMineral){
                        this->block[i][j] = new class miner(this->block[i][j]->dir);
                        this->block[i][j]->type = type::uncuttableMineral;
                        this->block[i][j]->curTime = curTime;
                        auto curminer= dynamic_cast<class miner*>(this->block[i][j]);
                        curminer->mineral->type = type::uncuttableMineral;
                    }
                    else{
                        this->block[i][j] = new class miner(this->block[i][j]->dir);
                        this->block[i][j]->type = type::NullMineral;
                        this->block[i][j]->curTime = curTime;
                    }

                }
                if(this->block[i][j]->devicetype == devicetype::trashbin){
                    if(this->block[i][j]->type == type::cuttableMineral){
                        this->block[i][j] = new class trashbin();
                        this->block[i][j]->type = type::cuttableMineral;
                    }
                    else if(this->block[i][j]->type == type::uncuttableMineral){
                        this->block[i][j] = new class trashbin();
                        this->block[i][j]->type = type::uncuttableMineral;
                    }
                    else{
                        this->block[i][j] = new class trashbin();
                        this->block[i][j]->type = type::NullMineral;
                    }
                }
                if(this->block[i][j]->devicetype == devicetype::transition){
                    if(this->block[i][j]->type == type::cuttableMineral){
                        this->block[i][j]= new class transition(this->block[i][j]->dir);
                        this->block[i][j]->type = type::cuttableMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                    else if(this->block[i][j]->type == type::uncuttableMineral){
                        this->block[i][j] =new class transition(this->block[i][j]->dir);
                        this->block[i][j]->type = type::uncuttableMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                    else{
                        this->block[i][j] = new class transition(this->block[i][j]->dir);
                        this->block[i][j]->type = type::NullMineral;
                        this->block[i][j]->curTime = curTime;
                    }
                }
            }
        }

        loadFile.close();
        qDebug() << "Game loaded successfully!";
    } else {
        qDebug() << "Could not open file for reading:" << loadFile.errorString();
    }
}


