
QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    centre.cpp \
    conveyor.cpp \
    cursor.cpp \
    cutter.cpp \
    helpscene.cpp \
    levelupscene.cpp \
    machine.cpp \
    main.cpp \
    miner.cpp \
    mineral.cpp \
    mypushbutton.cpp \
    object.cpp \
    playscene.cpp \
    scene.cpp \
    startscene.cpp \
    transition.cpp \
    trashbin.cpp \
    widget.cpp

HEADERS += \
    centre.h \
    conveyor.h \
    cursor.h \
    cutter.h \
    headerfiletouse.h \
    helpscene.h \
    levelupscene.h \
    machine.h \
    miner.h \
    mineral.h \
    mypushbutton.h \
    object.h \
    parameter.h \
    playscene.h \
    scene.h \
    startscene.h \
    transition.h \
    trashbin.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc \
    music.qrc

DISTFILES += \
    savedGame
