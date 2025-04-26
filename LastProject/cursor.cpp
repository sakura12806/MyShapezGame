#include "cursor.h"


Cursor::Cursor()
{
    this->obj = new class object();
}
Cursor::Cursor(object *obj, int x, int y){
    this->obj = obj;
    this->pos.pos_x = x;
    this->pos.pos_y = y;
}
