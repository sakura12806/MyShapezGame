#include "startscene.h"

startScene::startScene()
{
    //实现标题
    setTitle();
    //实现开始按钮
    setStartButton();
    //实现商店按钮
    setLevelUpButton();
    //实现帮助按钮
    setHelpButton();
    setsaveButton();
    //musicplay();
    setTxt(&txt_intro);
}
void startScene::setTitle(){
    title = new myPushButton;
    title->setStyleSheet("QPushButton{border-image: url(:/Images/logo/logo.png)}");
    title -> move(GAME_WIDTH / 4, GAME_HEIGHT / 5);
    title->setFixedSize(710, 180);
    title -> setParent(this);
}

void startScene::setStartButton()
{
    start = new myPushButton;
    start->move(GAME_WIDTH / 4, 3* GAME_HEIGHT / 4);
    start->setFixedSize(100, 100);
    start->setStyleSheet("QPushButton{border-image: url(:/Images/button/play.png)}");
    start->setParent(this);
}

void startScene::setLevelUpButton()
{
    levelUp = new myPushButton;
    levelUp->move(GAME_WIDTH / 2, 3* GAME_HEIGHT / 4);
    levelUp->setFixedSize(100, 100);
    levelUp->setStyleSheet("QPushButton{border-image: url(:/Images/button/shop.png)}");
    levelUp->setParent(this);
}

void startScene::setHelpButton()
{
    help = new myPushButton;
    help->move(3 * GAME_WIDTH / 4, 3* GAME_HEIGHT / 4);
    help->setFixedSize(100, 100);
    help->setStyleSheet("QPushButton{border-image: url(:/Images/button/main_menu_settings.png)}");
    help->setParent(this);
}

void startScene::setsaveButton(){
    save = new myPushButton;
    save->setFixedSize(100, 100);
    save->move(GAME_WIDTH - 100, 0);

    save->setStyleSheet("QPushButton{border-image: url(:/Images/save.png)}");
    save->setParent(this);

}
void startScene::setTxt(QTextEdit * txt)
{
    txt->setReadOnly(true);
    txt->setParent(this);
    txt->setFixedSize(300, 340);
    txt->setText("点击左侧按钮为开始游戏\n"
                 "点击中间按钮为升级界面\n"
                 "点击右侧按钮为规则界面\n"
                 "点击右上角按钮保存和修改存档(请记得及时保存存档哦！）\n"
                 "存档第一行是money，请不要随意修改并保存存档，否则可能造成未知错误（");
    txt->setStyleSheet("background: transparent; color: black; border-style: outset; font: bold 25px; font-family: 微软雅黑;");

}
