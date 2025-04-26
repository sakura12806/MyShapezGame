#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QTimer>
#include <QSettings>
#include "helpscene.h"
#include "startscene.h"
#include "playscene.h"
#include "levelupscene.h"
//#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //界面
    startScene *start;
    playScene *game;
    levelupscene *levelup;
    helpscene *help;
    //
    //信号与槽的连接
    void connections();

    //全局变量 钱和各种机器速率


    void flashbutton(QPushButton *button);
    void musicplay();
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    //QTimer* operateTimer;
private:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    bool isFirstTime = true;

    void onStartButtonClicked();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
