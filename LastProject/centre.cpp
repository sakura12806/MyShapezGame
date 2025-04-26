#include "centre.h"

centre::centre()
{
    this->type = type::centre;
    this->devicetype = devicetype::Null;
    this->curTime =0;
    this->mineral = new class NullMineral;
    this->icon.load(":/Images/device/centre.png");
    this->dir = direction::up;
}
void centre::changeDirection(direction dir){

}
