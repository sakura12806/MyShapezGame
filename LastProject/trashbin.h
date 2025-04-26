#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <QObject>
#include "machine.h"

class trashbin: public machine
{
public:
    trashbin();
    void changeDirection(direction dir);
};

#endif // TRASHBIN_H
