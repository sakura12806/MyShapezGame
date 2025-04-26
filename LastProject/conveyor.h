#ifndef CONVEYOR_H
#define CONVEYOR_H

#include <QObject>
#include "machine.h"

class conveyor: public machine
{
public:
    conveyor();
    conveyor(direction dir);
    void changeDirection(direction dir);
};

#endif // CONVEYOR_H
