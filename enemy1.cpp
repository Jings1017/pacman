#include "enemy1.h"
#include "game_window.h"
#include "ui_Game_window.h"
#include "map.h"
#include "energizer.h"
#include <QGraphicsScene>
#include <QTime>
#include <QFile>
#include <QString>
#include "pacman.h"


#define LEFT  1
#define UP    2
#define DOWN  3
#define RIGHT 4
Enemy1 :: ~Enemy1()
{
}

int Enemy1 :: move(int pac_x,int pac_y, int ghost1_x,int ghost1_y)
{

        if(ghost1_x==pac_x && ghost1_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost1_x==pac_x && ghost1_y>pac_y)
        {
            return UP ;
        }
        else if (ghost1_x<pac_x && ghost1_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost1_x>pac_x && ghost1_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost1_x<pac_x && ghost1_y<pac_y)
        {
            return RIGHT ;
        }
        else if (ghost1_x<pac_x && ghost1_y>pac_y)
        {
            return RIGHT;
        }
        else if (ghost1_x>pac_x && ghost1_y<pac_y)
        {
            return LEFT ;
        }
        else if (ghost1_x>pac_x && ghost1_y>pac_y)
        {
            return LEFT ;
        }

}

int Enemy1 :: scaredmove(int pac_x,int pac_y, int ghost1_x,int ghost1_y)
{

        if(ghost1_x==pac_x && ghost1_y<pac_y)
        {
            return UP ;
        }
        else if (ghost1_x==pac_x && ghost1_y>pac_y)
        {
            return DOWN ;
        }
        else if (ghost1_x<pac_x && ghost1_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost1_x>pac_x && ghost1_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost1_x<pac_x && ghost1_y<pac_y)
        {
            return LEFT ;
        }
        else if (ghost1_x<pac_x && ghost1_y>pac_y)
        {
            return LEFT;
        }
        else if (ghost1_x>pac_x && ghost1_y<pac_y)
        {
            return RIGHT ;
        }
        else if (ghost1_x>pac_x && ghost1_y>pac_y)
        {
            return RIGHT ;
        }

}
