#ifndef TRANSITION_H
#define TRANSITION_H
#include <QObject>
#include "machine.h"


class transition: public machine
{
public:
    transition();
    transition(direction dir);
    void changeDirection(direction dir);
};

#endif // TRANSITION_H
