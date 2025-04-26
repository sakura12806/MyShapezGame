#include "miner.h"
#include "qdebug.h"

miner::miner()
{
    this ->mineral = new class NullMineral;
    this ->devicetype = devicetype::miner;
    this ->curTime = 0;
    this ->rate = 0.5;

    this->icon.load(":/Images/device/miner_up.png");
}

miner::miner(direction dir)
{
    this ->devicetype = devicetype::miner;
    this ->mineral = new class NullMineral;
    this ->curTime = 0;
    this ->rate = 0.5;
    this ->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/miner_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/miner_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/miner_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/miner_down.png");
    }
}
/*
void miner::mine(object *obj) {
    if(obj->type == type::cuttableMineral || obj->type == type::uncuttableMineral){
        this ->mineral = (Mineral* )obj;
    }
}
*/
void miner::changeDirection(direction dir)
{
    this->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/miner_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/miner_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/miner_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/miner_down.png");
    }
}



