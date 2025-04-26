#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMediaPlayer>
#include <QSoundEffect>
#include <QAudioOutput>
//#include <QMediaPlaylist>
#include "scene.h"
#include <QTextEdit>
class startScene: public scene
{
public:
    startScene();

    void setTitle();
    //开始按钮
    void setStartButton();
    //升级按钮
    void setLevelUpButton();
    //帮助按钮
    void setHelpButton();

    void setsaveButton();
    void setTxt(QTextEdit *);
    //void musicplay();

    bool isplay;
    //绘图事件重构
    //void paintEvent(QPaintEvent *);

    myPushButton *title, *start, *levelUp, *help, *save;
private:
    QTextEdit txt_intro;
};

#endif // STARTSCENE_H
