#include "trashbin.h"

trashbin::trashbin()
{
    this->devicetype = devicetype::trashbin;
    this->mineral = new class NullMineral;
    this->dir = direction::up;
    this->curTime = 0;
    this->rate = 1;
    this->icon.load(":/Images/device/trash.png");
}
void trashbin::changeDirection(direction dir){

}
