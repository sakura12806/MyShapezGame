#ifndef LEVELUPSCENE_H
#define LEVELUPSCENE_H

#include "scene.h"
#include <QTextEdit>
#include "Mypushbutton.h"
#include "playscene.h"
#include <QString>
class levelupscene: public scene
{
public:
    levelupscene();
    void paintEvent(QPaintEvent *);
    //按钮的初始化
    void setButton(QPushButton *);
    //文本框的初始化
    void setTxt(QTextEdit *);
    void loadPixmap();

    QPushButton upgrade_miner, upgrade_cutter, upgrade_conveyor, upgrade_transition, upgrade_mapsize, upgrade_centresize;
    //图片
    QPixmap pixminer1, pixcutter1, pixconveyor1, pixminer2, pixcutter2, pixconveyor2, pixtransition, money_, pixcentre, pixmap;
    //文本框
    QTextEdit txt_miner, txt_cutter, txt_conveyor, txt_transition, txt_map, txt_centre, txt_salary, txt_func;
    //参数
    //int money = ;
    //把参数转换成QString类型, 方便输出
    //QString salary, func;
};

#endif // LEVELUPSCENE_H
