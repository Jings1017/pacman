#include "enemy3.h"

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
Enemy3 :: ~Enemy3()
{
}

int Enemy3 :: move(int pac_x,int pac_y, int ghost3_x,int ghost3_y)
{

        if(ghost3_x==pac_x && ghost3_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost3_x==pac_x && ghost3_y>pac_y)
        {
            return UP;
        }
        else if (ghost3_x<pac_x && ghost3_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost3_x>pac_x && ghost3_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost3_x<pac_x && ghost3_y<pac_y)
        {
            return UP ;
        }
        else if (ghost3_x<pac_x && ghost3_y>pac_y)
        {
            return RIGHT;
        }
        else if (ghost3_x>pac_x && ghost3_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost3_x>pac_x && ghost3_y>pac_y)
        {
            return LEFT ;
        }

}

int Enemy3 :: scaredmove(int pac_x,int pac_y, int ghost3_x,int ghost3_y)
{

        if(ghost3_x==pac_x && ghost3_y<pac_y)
        {
            return UP ;
        }
        else if (ghost3_x==pac_x && ghost3_y>pac_y)
        {
            return DOWN;
        }
        else if (ghost3_x<pac_x && ghost3_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost3_x>pac_x && ghost3_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost3_x<pac_x && ghost3_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost3_x<pac_x && ghost3_y>pac_y)
        {
            return LEFT;
        }
        else if (ghost3_x>pac_x && ghost3_y<pac_y)
        {
            return UP ;
        }
        else if (ghost3_x>pac_x && ghost3_y>pac_y)
        {
            return RIGHT ;
        }

}


