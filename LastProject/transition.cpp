#include "transition.h"

transition::transition()
{
    this ->mineral = new class NullMineral;
    this ->devicetype = devicetype::transition;
    this ->curTime = 0;
    this ->rate = 0.5;
    this->icon.load(":/Images/device/transition_up.png");
}

transition::transition(direction dir)
{
    this ->devicetype = devicetype::transition;
    this ->mineral = new class NullMineral;
    this ->curTime = 0;
    this ->rate = 0.5;
    this ->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/transition_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/transition_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/transition_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/transition_down.png");
    }
}
void transition::changeDirection(direction dir)
{
    this->dir = dir;
    if(dir == direction::up){
        this->icon.load(":/Images/device/transition_up.png");
    }else if(dir == direction::right){
        this->icon.load(":/Images/device/transition_right.png");
    }else if(dir == direction::left){
        this->icon.load(":/Images/device/transition_left.png");
    }else if(dir == direction::down){
        this->icon.load(":/Images/device/transition_down.png");
    }
}
