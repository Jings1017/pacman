#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T21:16:16
#
#-------------------------------------------------

QT += core gui
QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PacMan_git
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    map.cpp \
    pacman.cpp \
    ghost.cpp \
    sounds.cpp \
    dots.cpp \
    textboard.cpp \
    energizer.cpp \
    game_window.cpp \
    enemy.cpp \
    enemy1.cpp \
    enemy2.cpp \
    enemy3.cpp \
    enemy4.cpp

HEADERS += \
    map.h \
    pacman.h \
    ghost.h \
    sounds.h \
    dots.h \
    energizer.h \
    textboard.h \
    game_window.h \
    enemy.h \
    enemy1.h \
    enemy2.h \
    enemy3.h \
    enemy4.h

FORMS += \
    Game_window.ui

RESOURCES += \
    images.qrc \
    sounds.qrc

DISTFILES +=
