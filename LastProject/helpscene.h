#ifndef HELPSCENE_H
#define HELPSCENE_H

#include <QTextEdit>
#include "scene.h"
#include <QObject>

class helpscene: public scene
{
public:
    helpscene();

    void paintEvent(QPaintEvent *);
    //按钮的初始化
    //void setButton(QPushButton *);
    //文本框的初始化
    void setTxt(QTextEdit *);
    void loadPixmap();
    void setTxt1(QTextEdit *);
    //文本框
private:
    QTextEdit txt_miner, txt_cutter, txt_conveyor, txt_transition, txt_map, txt_centre, txt_salary, txt_mission, txt_operate;
    QTextEdit txt_total, txt_func;
    QPixmap pixminer, pixcutter, pixconveyor, pixtransition, money_, pixcentre, pixmap;
};

#endif // HELPSCENE_H
