#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include "mypushbutton.h"
#include "headerfiletouse.h"

class scene : public QWidget{
    Q_OBJECT
public:
    scene();
    //初始化返回键
    void backButton();
    //背景图片
    //QPixmap background;
    //返回键
    myPushButton *back;
    static int money;
};

#endif // SCENE_H
