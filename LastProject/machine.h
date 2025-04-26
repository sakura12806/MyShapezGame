#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "mineral.h"
#include "parameter.h"
#include "object.h"


class machine: public object
{
public:
    machine();

    Mineral* mineral;
    double rate;
    virtual void changeDirection(direction dir)=0;
};

#endif // MACHINE_H
