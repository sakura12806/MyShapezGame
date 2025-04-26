#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>
#include "object.h"
#include "machine.h"

struct Pos{
    int pos_x, pos_y;
};

class Cursor
{
public:
    Cursor();
    Cursor(object *obj, int x, int y);
    object *obj;
    Pos pos;
};

#endif // CURSOR_H
