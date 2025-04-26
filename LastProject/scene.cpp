#include "scene.h"

int scene::money = 0;
scene::scene()
{
    //设置窗口尺寸
    this->setFixedSize(GAME_WIDTH, GAME_HEIGHT);
    //this -> showFullScreen();

    //设置窗口图标
    this->setWindowIcon(QIcon(":/Images/logo/opensea.png"));

    //设置窗口名字
    this->setWindowTitle(GAME_TiTLE);

    //设置窗口背景
    //background.load(GAME_BACKGROUND);
}


//返回键初始化
void scene::backButton()
{
    back = new myPushButton;
    back->setParent(this);
    back->move(GAME_WIDTH - 180, GAME_HEIGHT - 120);
    back->setFixedSize(100, 100);
    back->setStyleSheet("QPushButton{border-image: url(:/Images/button/back.png)}");
}
