#ifndef MINER_H
#define MINER_H

#include <QObject>
#include "machine.h"

class miner: public machine
{
public:
    miner();
    miner(direction dir);
    //void mine(object *obj);
    void changeDirection(direction dir);
};

#endif // MINER_H
