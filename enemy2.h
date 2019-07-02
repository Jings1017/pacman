#ifndef ENEMY2_H
#define ENEMY2_H

#include "enemy.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QMediaPlayer>
#include <QGraphicsScene>
#include <QLabel>

#include "map.h"
#include "pacman.h"
#include "energizer.h"
#include "dots.h"
#include "ghost.h"
#include "textboard.h"
#include "sounds.h"

class Enemy2 : public Enemy
{
public:
    int move(int, int, int, int);
    int scaredmove(int, int, int, int);
    ~Enemy2();

};

#endif // ENEMY2_H
