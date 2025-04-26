#ifndef MINERAL_H
#define MINERAL_H

#include <QObject>
#include <QColor>
#include "parameter.h"
#include "object.h"

class Mineral: public object
{
public:
    Mineral();
    int value;
    bool isCuttable;

};

class cuttableMineral: public Mineral
{
public:
    cuttableMineral();
};

class uncuttableMineral: public Mineral
{
public:
    uncuttableMineral();
};

class halfCuttableMineralleft: public Mineral
{
public:
    halfCuttableMineralleft();
};

class halfCuttableMineralright: public Mineral
{
public:
    halfCuttableMineralright();
};

class quarterCuttableMineral: public Mineral
{
public:
    quarterCuttableMineral();
};

class NullMineral: public Mineral
{
public:
    NullMineral();
};

#endif // MINERAL_H
