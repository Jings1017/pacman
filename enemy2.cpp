#include "enemy2.h"

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
Enemy2 :: ~Enemy2()
{
}

int Enemy2 :: move(int pac_x,int pac_y, int ghost2_x,int ghost2_y)
{

        if(ghost2_x==pac_x && ghost2_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost2_x==pac_x && ghost2_y>pac_y)
        {
            return UP;
        }
        else if (ghost2_x<pac_x && ghost2_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost2_x>pac_x && ghost2_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost2_x<pac_x && ghost2_y<pac_y)
        {
            return RIGHT ;
        }
        else if (ghost2_x<pac_x && ghost2_y>pac_y)
        {
            return UP;
        }
        else if (ghost2_x>pac_x && ghost2_y<pac_y)
        {
            return LEFT ;
        }
        else if (ghost2_x>pac_x && ghost2_y>pac_y)
        {
            return DOWN ;
        }

}

int Enemy2 :: scaredmove(int pac_x,int pac_y, int ghost2_x,int ghost2_y)
{

        if(ghost2_x==pac_x && ghost2_y<pac_y)
        {
            return UP ;
        }
        else if (ghost2_x==pac_x && ghost2_y>pac_y)
        {
            return DOWN;
        }
        else if (ghost2_x<pac_x && ghost2_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost2_x>pac_x && ghost2_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost2_x<pac_x && ghost2_y<pac_y)
        {
            return LEFT ;
        }
        else if (ghost2_x<pac_x && ghost2_y>pac_y)
        {
            return DOWN;
        }
        else if (ghost2_x>pac_x && ghost2_y<pac_y)
        {
            return RIGHT ;
        }
        else if (ghost2_x>pac_x && ghost2_y>pac_y)
        {
            return UP ;
        }

}


