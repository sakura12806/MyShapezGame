#include "cutter.h"

cutter::cutter():machine() {
    this->mineral = new class NullMineral;
    this->devicetype = devicetype::cutter;
    this->rate = 0.1;
    this->icon.load(":/Images/device/cutter_up.png");
}

cutter::cutter(direction dir) {
    this->devicetype = devicetype::cutter;
    this->mineral = new class NullMineral;
    this->dir = dir;
    this->curTime = 0;
    this->rate = 0.1;

    if(dir == direction::up){
        this->icon.load(":/Images/device/cutter_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/cutter_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/cutter_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/cutter_down.png");
    }
}

void cutter::changeDirection(direction dir){
    this->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/cutter_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/cutter_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/cutter_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/cutter_down.png");
    }
}
