#ifndef ENEMY1_H
#define ENEMY1_H
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

class Enemy1 : public Enemy
{
public:
    int move(int, int, int, int);
    int scaredmove(int, int, int, int);
    ~Enemy1();

};

#endif // ENEMY1_H
