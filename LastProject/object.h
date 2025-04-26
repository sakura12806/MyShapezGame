#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <qpixmap.h>
/*****************方向***********************/
enum direction{
    up,
    down,
    left,
    right,
    uptoright,
    righttodown,
    downtoleft,
    lefttoup,
    uptoleft,
    righttoup,
    downtoright,
    lefttodown,g
};

/*****************地图上的设备和矿物***********************/
enum type{

    cuttableMineral,
    uncuttableMineral,
    halfCuttableMineralleft,
    halfCuttableMineralright,
    quarterCuttableMineral,
    NullMineral,
    centre,
};
enum devicetype{
    miner,
    cutter,
    cutternext,
    conveyor,
    trashbin,
    transition,
    Null
};
enum mineralOnConveyor{
    cuttableMineralsmall,
    uncuttableMineralsmall,
    halfCuttableMineralleftsmall,
    halfCuttableMineralrightsmall,
    NullMineralon,
};

class object :public QObject
{
public:
    object();
    type type;
    devicetype devicetype;
    mineralOnConveyor mineraltype;
    QPixmap icon;
    int curTime;
    direction dir;

};

#endif // OBJECT_H
