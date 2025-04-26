#include "levelupscene.h"

levelupscene::levelupscene()
{
    backButton();

    //加载图片
    loadPixmap();
    //初始化文本框
    setTxt(&txt_miner);
    setTxt(&txt_cutter);
    setTxt(&txt_conveyor);
    setTxt(&txt_salary);
    setTxt(&txt_transition);
    setTxt(&txt_centre);
    setTxt(&txt_map);
    setTxt(&txt_func);
    //初始化按钮
    setButton(&upgrade_miner);
    setButton(&upgrade_cutter);
    setButton(&upgrade_conveyor);
    setButton(&upgrade_transition);
    setButton(&upgrade_mapsize);
    setButton(&upgrade_centresize);
}
void levelupscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 30, 100, 100, pixminer1);
    painter.drawPixmap(GAME_WIDTH / 5 * 2 - 100, GAME_HEIGHT / 30 + 30, 200, 100, pixcutter1);
    painter.drawPixmap(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 30, 100, 100, pixconveyor1);
    painter.drawPixmap(GAME_WIDTH / 5 * 4 + 60, GAME_HEIGHT / 30 + 30, 100, 100,money_);
    painter.drawPixmap(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 350, 100, 100, pixtransition);
    painter.drawPixmap(GAME_WIDTH / 5 * 2 - 100, GAME_HEIGHT / 30 + 350, 200, 100, pixmap);
    painter.drawPixmap(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 350, 100, 100, pixcentre);
    //介绍文本
    txt_miner.setText("增加开采器速率50%\n价格: 50\n");
    txt_miner.move(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 150);
    txt_cutter.setText("增加切割机速率50%\n价格: 50\n");
    txt_cutter.move(GAME_WIDTH / 5 * 2 - 50, GAME_HEIGHT / 30 + 150);
    txt_conveyor.setText("增加传送带速率50%\n价格: 50\n");
    txt_conveyor.move(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 150);

    txt_transition.setText("增加旋转器速率50%\n价格: 50\n");
    txt_transition.move(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 470);
    txt_map.setText("增加开采物地块大小，限制level4\n价格: 200\n");
    txt_map.move(GAME_WIDTH / 5 * 2 - 50, GAME_HEIGHT / 30 + 470);
    txt_centre.setText("增加交付中心大小\n价格: 100\n");
    txt_centre.move(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 470);

    txt_salary.setText(QString("Current Money: %1").arg(scene::money));
    txt_salary.move(GAME_WIDTH / 5 * 4 + 60, GAME_HEIGHT / 30 + 150);
    //txt_func.setText(func);
    //txt_func.move(GAME_WIDTH / 5 * 3 - 100, GAME_HEIGHT / 30 + 60);

    upgrade_miner.move(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 250);
    upgrade_miner.show();
    upgrade_cutter.move(GAME_WIDTH / 5 * 2 - 50, GAME_HEIGHT / 30 + 250);
    upgrade_cutter.show();
    upgrade_conveyor.move(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 250);
    upgrade_conveyor.show();

    upgrade_transition.move(GAME_WIDTH / 5 - 100, GAME_HEIGHT / 30 + 570);
    upgrade_transition.show();
    upgrade_mapsize.move(GAME_WIDTH / 5 * 2 - 50, GAME_HEIGHT / 30 + 570);
    upgrade_mapsize.show();
    upgrade_centresize.move(GAME_WIDTH / 5 * 3, GAME_HEIGHT / 30 + 570);
    upgrade_centresize.show();
}

void levelupscene::setButton(QPushButton * button)
{
    button->setParent(this);
    button->setFixedSize(120, 60);
    button->setStyleSheet("QPushButton{border-image: url(:/Images/device/upgrade.png)}");
}

//文本框初始化
void levelupscene::setTxt(QTextEdit * txt)
{
    txt->setReadOnly(true);
    txt->setParent(this);
    txt->setFixedSize(300, 200);
    txt->setStyleSheet("background: transparent; color: black; border-style: outset; font: bold 20px; font-family: 微软雅黑;");
}
void levelupscene::loadPixmap()
{
    pixminer1.load(":/Images/device/miner_up_new.png");
    pixminer2.load(":/Images/device/miner_up_new.png");
    pixcutter1.load(":/Images/device/cutter_up_new.png");
    pixcutter2.load(":/Images/device/cutter_up_new.png");
    pixconveyor1.load(":/Images/device/conveyor_up_new.png");
    pixconveyor2.load(":/Images/device/conveyor_up_new.png");
    pixtransition.load(":/Images/device/transition_up.png");
    pixcentre.load(":/Images/device/centre.png");
    pixmap.load(":/Images/device/map.png");
    money_.load(":/Images/money_.png");
}
/*
void levelupscene::pass_on(int a)
{
    money = a;
    salary = QString::number(a);
}
*/
