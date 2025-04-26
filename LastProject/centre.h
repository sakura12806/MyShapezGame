#ifndef CENTRE_H
#define CENTRE_H

#include <QObject>
#include "object.h"
#include "mineral.h"
#include "machine.h"

class centre: public machine
{
public:
    centre();
    //Mineral* mineral;
    void changeDirection(direction dir);
};

#endif // CENTRE_H
