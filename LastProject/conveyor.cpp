#include "conveyor.h"

conveyor::conveyor()
{
    this->curTime = 0;
    this->mineral = new class NullMineral;
    this->devicetype = devicetype::conveyor;
    this->rate = 0.5;
    this->mineraltype = mineralOnConveyor::NullMineralon;
    this->icon.load(":/Images/device/conveyor_up.png");
}
conveyor::conveyor(direction dir){
    this->curTime = 0;
    this->rate = 0.5;
    this->mineral = new class NullMineral;
    this->mineraltype = mineralOnConveyor::NullMineralon;
    this->devicetype = devicetype::conveyor;
    this->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/conveyor_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/conveyor_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/conveyor_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/conveyor_down.png");
    }else if(dir == direction::downtoleft){
        this->icon.load(":/Images/device/conveyor_down_to_left.png");
    }else if(dir == direction::lefttodown){
        this->icon.load(":/Images/device/conveyor_left_to_down.png");
    }else if(dir == direction::downtoright){
        this->icon.load(":/Images/device/conveyor_down_to_right.png");
    }else if(dir == direction::righttodown){
        this->icon.load(":/Images/device/conveyor_right_to_down.png");
    }else if(dir == direction::uptoleft){
        this->icon.load(":/Images/device/conveyor_up_to_left.png");
    }else if(dir == direction::lefttoup){
        this->icon.load(":/Images/device/conveyor_left_to_up.png");
    }else if(dir == direction::uptoright){
        this->icon.load(":/Images/device/conveyor_up_to_right.png");
    }else if(dir == direction::righttoup){
        this->icon.load(":/Images/device/conveyor_right_to_up.png");
    }
}
void conveyor::changeDirection(direction dir){
    this->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/conveyor_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/conveyor_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/conveyor_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/conveyor_down.png");
    }else if(dir == direction::downtoleft){
        this->icon.load(":/Images/device/conveyor_down_to_left.png");
    }else if(dir == direction::lefttodown){
        this->icon.load(":/Images/device/conveyor_left_to_down.png");
    }else if(dir == direction::downtoright){
        this->icon.load(":/Images/device/conveyor_down_to_right.png");
    }else if(dir == direction::righttodown){
        this->icon.load(":/Images/device/conveyor_right_to_down.png");
    }else if(dir == direction::uptoleft){
        this->icon.load(":/Images/device/conveyor_up_to_left.png");
    }else if(dir == direction::lefttoup){
        this->icon.load(":/Images/device/conveyor_left_to_up.png");
    }else if(dir == direction::uptoright){
        this->icon.load(":/Images/device/conveyor_up_to_right.png");
    }else if(dir == direction::righttoup){
        this->icon.load(":/Images/device/conveyor_right_to_up.png");
    }
}
