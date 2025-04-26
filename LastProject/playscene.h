#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "scene.h"
#include "mineral.h"
#include "machine.h"
#include "object.h"
#include "miner.h"
#include "cutter.h"
#include "conveyor.h"
#include "trashbin.h"
#include "transition.h"
#include "centre.h"
#include "cursor.h"
#include <QTimer>
#include <QBrush>
#include <QTextEdit>
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


enum levelType{
    level1,
    level2,
    level3,
    level4,
};


class playScene: public scene
{
public:
    playScene();
    //初始化
    void init();

    //判断有无开采物
    bool isResource;
    //开采按钮
    void setMinerButton();
    //传送带按钮
    void setBeltButton();
    //切割机按钮
    void setCutterButton();
    //垃圾桶按钮
    void setTrashButton();
    void setTransitionButton();
    //升级按钮
    void setLevelUpButton();
    //帮助按钮
    void setHelpButton();
    //绘图事件重构
    void paintEvent(QPaintEvent *);
    //鼠标滚轮重构
    //void wheelEvent(QWheelEvent *event);
    //创建按钮
    myPushButton *minerbutton, *belt, *cutter, *trash, *transitionbutton, *levelUp, *help;


    //方格大小
    static int gridSize;
    int maxX = GAME_WIDTH/gridSize;
    int maxY = GAME_HEIGHT/gridSize;
    //static int maxX;
    //static int maxY;
    int SIZE = 60;

    //基本框架
    QVector<QVector<object*>> block;
    levelType leveltype;
    int mapUpgradeTimes = 0;
    Cursor* cursor;
    //mineral and machine
    class cuttableMineral cuttableMineral;
    class uncuttableMineral uncuttableMineral;
    class halfCuttableMineralleft halfmineralleft;
    class halfCuttableMineralright halfmineralright;
    class centre centre;


    //键盘事件重构
    void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void connections();

    //必要的文字说明，画面右上方的信息
    void setTxt(QTextEdit *);
    QTextEdit declaration;
    QTextEdit currentmission1;
    QTextEdit currentmoney;

    //
    void blockInit();
    //void settleObject(int i, int j, type objecttype);
    void scaleForObject(int start_i, int end_i, int start_j, int end_j, type objecttype);
    void level1();
    void upgradecentre();
    void upgrademap();
    void levelInit();
    bool isCentreUpgrade = false;
    bool isMapUpgrade = false;

    //operate
    void mineroperate(int x, int y);
    void conveyoroperate(int x, int y);
    void cutteroperate(int x, int y);
    void trashbinoperate(int x, int y);
    void transitionoperate(int x, int y);
    void centreoperate(int x, int y);
    void totaloperate();
    QTimer* operateTimer;

    //各种设备的工作间隔
    void updatetime(int x, int y);
    static int minerinterval;
    static int conveyorinterval;
    static int cutterinterval;
    static int transitioninterval;

    //mission
    //
    const int cuttablemineraltarget = 20;
    const int uncuttablemineraltarget = 30;
    const int halfminerallefttarget = 50;
    bool ismission1 = false;
    bool ismission2 = false;
    bool ismission3 = false;
    static int cuttablemineralnum;
    static int uncuttablemineralnum;
    static int halfmineralnum;
    void mission1(class centre *curcentre);
    void mission2(class centre *curcentre);
    void mission3(class centre *curcentre);
    void missionjudge();

    //存档的导入与导出

    void saveGame();
    void loadGame();
};

#endif // PLAYSCENE_H
