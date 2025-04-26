#include "helpscene.h"

helpscene::helpscene()
{
    backButton();
    loadPixmap();
    //初始化文本框
    setTxt(&txt_miner);
    setTxt(&txt_cutter);
    setTxt(&txt_conveyor);
    setTxt(&txt_salary);
    setTxt(&txt_transition);
    setTxt(&txt_centre);
    setTxt(&txt_map);
    setTxt1(&txt_total);
    setTxt(&txt_mission);
    setTxt(&txt_operate);
    setTxt1(&txt_func);
    //初始化按钮

}
void helpscene::setTxt(QTextEdit * txt)
{
    txt->setReadOnly(true);
    txt->setParent(this);
    //txt->setFixedSize(300, 200);
    txt->setStyleSheet("background: transparent; color: black; border-style: outset; font: bold 20px; font-family: 微软雅黑;");
}
void helpscene::setTxt1(QTextEdit * txt)
{
    txt->setReadOnly(true);
    txt->setParent(this);
    //txt->setFixedSize(300, 200);
    txt->setStyleSheet("background: transparent; color: red; border-style: outset; font: bold 30px; font-family: 微软雅黑;");
}
void helpscene::loadPixmap()
{
    pixminer.load(":/Images/device/miner_up_new.png");
    pixcutter.load(":/Images/device/cutter_up_new.png");
    pixconveyor.load(":/Images/device/conveyor_up_new.png");
    pixtransition.load(":/Images/device/transition_up.png");
    pixcentre.load(":/Images/device/centre.png");
    pixmap.load(":/Images/device/map.png");
    money_.load(":/Images/money_.png");
}
void helpscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(GAME_WIDTH / 8 - 60, GAME_HEIGHT / 30 + 330, 60, 60, pixminer);
    painter.drawPixmap(GAME_WIDTH / 8 * 2 - 60, GAME_HEIGHT / 30 + 330, 120, 60, pixcutter);
    painter.drawPixmap(GAME_WIDTH / 8 * 3, GAME_HEIGHT / 30 + 330, 60, 60, pixconveyor);

    painter.drawPixmap(GAME_WIDTH / 8 * 4, GAME_HEIGHT / 30 + 330, 60, 60, pixtransition);
    painter.drawPixmap(GAME_WIDTH / 8 * 5, GAME_HEIGHT / 30 + 330, 120, 60, pixmap);
    painter.drawPixmap(GAME_WIDTH / 8 * 6 +60, GAME_HEIGHT / 30 + 330, 60, 60, pixcentre);
    painter.drawPixmap(GAME_WIDTH / 8 * 7 + 60 , GAME_HEIGHT / 30 + 330, 60, 60,money_);
    //介绍文本
    txt_miner.setText("开采器\n可以升级3次");
    txt_miner.move(GAME_WIDTH / 8 - 60, GAME_HEIGHT / 30 + 400);
    txt_cutter.setText("切割机\n可以升级3次");
    txt_cutter.move(GAME_WIDTH / 8 * 2 - 60, GAME_HEIGHT / 30 + 400);
    txt_conveyor.setText("传送带\n可以升级3次");
    txt_conveyor.move(GAME_WIDTH / 8 * 3, GAME_HEIGHT / 30 + 400);

    txt_transition.setText("转换器\n可以将开采的\n或切割后的物\n品旋转180度");
    txt_transition.move(GAME_WIDTH /8 *4, GAME_HEIGHT / 30 + 400);
    txt_map.setText("地图上的物品分为可\n切割的和不可切割两种，\n你在level4可对地图升级");
    txt_map.move(GAME_WIDTH / 8 * 5, GAME_HEIGHT / 30 + 400);
    txt_centre.setText("交付中心\n你开采的物品都\n需要送到交付中\n心");
    txt_centre.setFixedHeight(120);
    txt_centre.move(GAME_WIDTH / 8 *6 +60, GAME_HEIGHT / 30 + 400);

    txt_salary.setText(QString("Current\nMoney: \n%1").arg(scene::money));
    txt_salary.setFixedHeight(120);
    txt_salary.move(GAME_WIDTH / 8 * 7 + 40, GAME_HEIGHT / 30 + 400);

    txt_total.setText("各位尊敬的玩家，请务必认真阅读游戏规则后再开始游戏！");
    txt_total.setFixedWidth(1280);
    txt_total.move(GAME_WIDTH / 8 - 80, GAME_HEIGHT / 30  - 15);

    txt_operate.setText("您的主任务是，用装置栏中的各个装置开采矿物，并将矿物交付给交付中心，以此获得金钱。\n"
                        "当然，你需要完成三局游戏，并升级level，你可以在游戏界面的右上角获得当前金钱和任务进度信息\n"
                        "\n"
                        "请注意：点击装置栏中的设备选中后，方向默认为向上，你可以在装置尚未放置时，按下‘R’键向右旋转。\n"
                        "若您选择传送带，你还可以按‘T’键，将传送带顺时针旋转，按‘F’键，将传送带逆时针旋转\n"
                        "举个例子，若您先按R键再按T键，此时传送带是右向下旋转，您也可以先按T键再按R键\n"
                        "在合法的位置，即没有被设备或交付中心占用的位置，点击鼠标左键即为放下装置\n"
                        "请您务必注意，您按下R键T键F键应当在装置尚未放置前，若您已经放置了装置，则操作无效\n"
                        "您可以一次性放置多个相同的装置，这将减少你鼠标的点击次数\n"
                        "您还可以对已经放置的装置，在对应位置点击鼠标右键，取消放置");
    txt_operate.setFixedWidth(1000);
    txt_operate.setFixedHeight(300);
    txt_operate.move(GAME_WIDTH / 8 - 50, GAME_HEIGHT / 30 + 40);
    txt_func.setText("您阅读好了吗？阅读好了就可以点击右侧×键进入游戏了！祝您游戏愉快！\n"
                     "如果您遇到问题可以联系3492713386@qq.com");
    txt_func.setFixedWidth(1000);
    txt_func.move(GAME_WIDTH / 8 - 50, GAME_HEIGHT / 30 + 500);

    txt_mission.setText("*需要注意，由于不可分割矿物更重，所以它的移动速度会慢于可分割矿物，可能需要您用眼睛补帧（");
    txt_mission.setFixedWidth(1000);
    txt_mission.move(GAME_WIDTH / 8 - 50, GAME_HEIGHT / 30 + 580);
}
