#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //创建界面
    start = new startScene;
    game = new playScene;
    levelup = new levelupscene;
    help = new helpscene;

    //开始
    start->show();

    //连接
    connections();
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player -> setSource(QUrl::fromEncoded("qrc:/music/music.mp3"));
    player->setLoops(5);
    musicplay();
    //operateTimer = new QTimer(this);

    // Connect the timer's timeout signal to the totaloperate slot


    // Start the timer with a 1000 ms interval (1 second)
    //operateTimer->start(1000);
}


Widget::~Widget()
{
    delete ui;
    delete start;

}

//信号与槽的连接，各按钮关系
void Widget::connections(){

    //开始界面的开始按钮
    connect(start->start, &QPushButton::clicked, this, [=](){
        //game->gridSize -= 20;

        if(this->isFirstTime == true){
        help->show();
        start->close();
        this->isFirstTime = false;}
        else if(this->isFirstTime == false){
        this->onStartButtonClicked();
        }
    });




    //开始界面的升级按钮
    connect(start->levelUp, &QPushButton::clicked, this, [=](){
        //game->operateTimer->start(1000);
        //game->gridSize -= 20;
        levelup->show();
        start->close();
    });

    connect(start->save, &QPushButton::clicked, this, [=](){
        //game->gridSize -= 20;
        game->saveGame();

    });
    //游戏界面的升级按钮
    connect(game->levelUp, &QPushButton::clicked, this, [=](){
        levelup->show();
        game->close();

    });

    //游戏界面的返回按钮
    connect(game->back, &QPushButton::clicked, this, [=](){
        //game->operateTimer->stop();
        start->show();
        game->close();
    });

    //升级界面的返回按钮
    connect(levelup->back, &QPushButton::clicked, this, [=](){
        game->show();
        levelup->close();
    });

    connect(help->back, &QPushButton::clicked, this, [=](){
        game->show();
        help->close();
    });

    connect(game->help, &QPushButton::clicked, this, [=](){
        help->show();
        game->close();
    });
    connect(start->help, &QPushButton::clicked, this, [=](){
        //game->operateTimer->start(1000);
        help->show();
        start->close();
    });
    connect(game->minerbutton, &QPushButton::clicked, this ,[=](){
        game->cursor->obj = new class miner(direction::up);
        qDebug() << "miner pressed";
        this->flashbutton(game->minerbutton);
    });
    connect(game->belt, &QPushButton::clicked, this ,[=](){
        game->cursor->obj = new class conveyor(direction::up);
        this->flashbutton(game->belt);
    });
    connect(game->cutter, &QPushButton::clicked, this ,[=](){
        game->cursor->obj = new class cutter(direction::up);
        this->flashbutton(game->cutter);
    });
    connect(game->trash, &QPushButton::clicked, this ,[=](){
        game->cursor->obj = new class trashbin();
        this->flashbutton(game->trash);
    });
    connect(game->transitionbutton, &QPushButton::clicked, this ,[=](){
        game->cursor->obj = new class transition(direction::up);
        this->flashbutton(game->transitionbutton);
    });

    //升级界面的按钮
    connect(&levelup->upgrade_miner, &QPushButton::clicked, this ,[=](){
        if(game->leveltype == level1){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
            if(scene::money >= 50){

                if(playScene::minerinterval == 5){
                    this->flashbutton(&levelup->upgrade_miner);
                    playScene::minerinterval =3;
                    scene::money -= 50;}
                else if(playScene::minerinterval == 3){
                    this->flashbutton(&levelup->upgrade_miner);
                    playScene::minerinterval = 2;
                    scene::money -= 50;
                }
                else{
                    QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
                }
            }
            else {
                // 钱不够
                QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
            }
        }
    });

    connect(&levelup->upgrade_cutter, &QPushButton::clicked, this ,[=](){
        if(game->leveltype == level1||game->leveltype == level2){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
        if(scene::money >= 50){

            if(playScene::cutterinterval == 5){
                this->flashbutton(&levelup->upgrade_cutter);
                playScene::cutterinterval =3;
                scene::money -= 50;}
            else if(playScene::cutterinterval == 3){
                this->flashbutton(&levelup->upgrade_cutter);
                playScene::cutterinterval = 2;
                scene::money -= 50;
            }
            else{
                QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
            }
        }
        else {
            // 钱不够
            QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
        }
        }
    });
    connect(&levelup->upgrade_conveyor, &QPushButton::clicked, this ,[=](){
        if(game->leveltype == level1){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
        if(scene::money >= 50){

            if(playScene::conveyorinterval == 5){
                this->flashbutton(&levelup->upgrade_conveyor);
                playScene::conveyorinterval =3;
                scene::money -= 50;}
            else if(playScene::conveyorinterval == 3){
                this->flashbutton(&levelup->upgrade_conveyor);
                playScene::conveyorinterval = 2;
                scene::money -= 50;
            }
            else{
                QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
            }
        }
        else {
            // 钱不够
            QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
        }
        }
    });
    connect(&levelup->upgrade_transition, &QPushButton::clicked, this ,[=](){
        if(game->leveltype == level1||game->leveltype == level2){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
        if(scene::money >= 50){

            if(playScene::transitioninterval == 5){
                this->flashbutton(&levelup->upgrade_transition);
                playScene::transitioninterval =3;
                scene::money -= 50;}
            else if(playScene::transitioninterval == 3){
                this->flashbutton(&levelup->upgrade_transition);
                playScene::transitioninterval = 2;
                scene::money -= 50;
            }
            else{
                QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
            }
        }
        else {
            // 钱不够
            QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
        }
        }
    });
    connect(&levelup->upgrade_mapsize, &QPushButton::clicked, this ,[=](){
        if(game->leveltype != level4){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
            if(game->isMapUpgrade == true){
                QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
            }
            else{
                if(scene::money >= 200){
                    this->flashbutton(&levelup->upgrade_mapsize);
                    scene::money -= 200;
                    game->upgrademap();
                }
                else {
                    // 钱不够
                    QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
                }
            }
        }
    });
    connect(&levelup->upgrade_centresize, &QPushButton::clicked, this ,[=](){
        if(game->leveltype == level1){
            QMessageBox::warning(this, "level Not Enough", "你的级别不够！");
        }
        else{
        if(scene::money >= 100){

            if(game->isCentreUpgrade == false){
                this->flashbutton(&levelup->upgrade_centresize);
                game->upgradecentre();
                scene::money -= 100;
            }
            else{
                QMessageBox::warning(this, "Upgrade Maxed", "你已升至满级！");
            }
        }
        else {
            // 钱不够
            QMessageBox::warning(this, "Money Not Enough", "你的钱币不够！");
        }
        }
    });
    /*
    connect(operateTimer, &QTimer::timeout, this, [=](){
        game->totaloperate();
    });
    */

}
void Widget::flashbutton(QPushButton* button) {

    QString originalStyle = button->styleSheet();
    button->setStyleSheet("background-color: yellow;");

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        button->setStyleSheet(originalStyle);
        timer->deleteLater();
    });

    timer->setInterval(300);
    timer->start();
}

void Widget::musicplay(){



    player->setAudioOutput(audioOutput );
    audioOutput->setVolume(0.5);

    player->play();
    qDebug() << "music play called";
    //player->setLoops(QMediaPlayer::Infinite);
    //connect(player, &QMediaPlayer::mediaStatus , this, &Widget::onMediaStatusChanged);

}
void Widget::onMediaStatusChanged(QMediaPlayer::MediaStatus status){
    // 当播放完成时重新开始播放
    // 如果当前播放位置等于总时长，说明播放完成，重新开始
    qDebug() << "music change";
    if(status == QMediaPlayer::EndOfMedia){
        qDebug() << "restart";
        player->setPosition(0);
        player->play();
    }
}
void Widget::onStartButtonClicked() {
    // 显示询问框
    QMessageBox msgBox;
    msgBox.setText("继续游戏？新游戏？返回当前存档进度？");
    //msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // 设置按钮文本

    QPushButton *continueButton = msgBox.addButton("继续游戏", QMessageBox::ActionRole);
    QPushButton *newButton = msgBox.addButton("新游戏", QMessageBox::ActionRole);
    QPushButton *saveButton = msgBox.addButton("返回存档进度", QMessageBox::ActionRole);
    //msgBox.setDefaultButton(continueButton);

    // 设置固定大小
    msgBox.setFixedSize(400, 200);

    // 获取用户的选择
    int ret = msgBox.exec();

    // 根据选择进行相应操作
    if (msgBox.clickedButton() == newButton) {

        game->init();
        //game->operateTimer->start(1000);
        //player->pause();
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);
        player->setPosition(0);
        player->play();
        help->show();
        start->close();
        // 用户选择开始新游戏

    } else if (msgBox.clickedButton() == continueButton) {

        //game->operateTimer->start(1000);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);
        player->setPosition(0);
        player->play();
        game->show();
        start->close();
        // 用户选择继续游戏

    }
    else if (msgBox.clickedButton() == saveButton) {
        game->loadGame();
        //game->operateTimer->start(1000);
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(0.5);
        player->setPosition(0);
        player->play();
        game->show();
        start->close();
        // 用户选择继续游戏

    }
}
