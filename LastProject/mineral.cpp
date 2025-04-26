#include "mineral.h"

Mineral::Mineral()
{
    this->devicetype = devicetype::Null;
    this->curTime = 0;
    this->dir = direction::up;

}
cuttableMineral::cuttableMineral(){
    this->isCuttable = true;
    this->value = 4;
    this->icon.load(":/Images/Resource/cuttableResource.png");
    this->type = type::cuttableMineral;
}
uncuttableMineral::uncuttableMineral(){
    this->isCuttable = false;
    this->value = 3;
    this->icon.load(":/Images/Resource/uncuttableResource.png");
    this->type = type::uncuttableMineral;
}
halfCuttableMineralleft::halfCuttableMineralleft(){
    this->isCuttable = false;
    this->value = 2;
    this->icon.load(":/Images/Resource/cuttableResourceleft.png");
    this->type = type::halfCuttableMineralleft;
}
halfCuttableMineralright::halfCuttableMineralright(){
    this->isCuttable = false;
    this->value = 2;
    this->icon.load(":/Images/Resource/cuttableResourceright.png");
    this->type = type::halfCuttableMineralright;
}
quarterCuttableMineral::quarterCuttableMineral(){
    this->isCuttable = false;
    this->value = 1;
    this->icon.load(":/Images/Resource/cuttableResource.png");
    this->type = type::quarterCuttableMineral;
}
NullMineral::NullMineral(){
    this->isCuttable = false;
    this->value = 1;
    this->type = type::NullMineral;
}
