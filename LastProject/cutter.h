#ifndef CUTTER_H
#define CUTTER_H

#include <QObject>
#include "machine.h"

class cutter: public machine
{
public:
    cutter();
    cutter(direction dir);

    void changeDirection(direction dir);
};

#endif // CUTTER_H
