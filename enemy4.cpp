#include "enemy4.h"

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
Enemy4 :: ~Enemy4()
{
}

int Enemy4 :: move(int pac_x,int pac_y, int ghost4_x,int ghost4_y)
{

        if(ghost4_x==pac_x && ghost4_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost4_x==pac_x && ghost4_y>pac_y)
        {
            return UP;
        }
        else if (ghost4_x<pac_x && ghost4_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost4_x>pac_x && ghost4_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost4_x<pac_x && ghost4_y<pac_y)
        {
            return UP ;
        }
        else if (ghost4_x<pac_x && ghost4_y>pac_y)
        {
            return UP;
        }
        else if (ghost4_x>pac_x && ghost4_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost4_x>pac_x && ghost4_y>pac_y)
        {
            return DOWN ;
        }

}

int Enemy4 :: scaredmove(int pac_x,int pac_y, int ghost4_x,int ghost4_y)
{

        if(ghost4_x==pac_x && ghost4_y<pac_y)
        {
            return UP ;
        }
        else if (ghost4_x==pac_x && ghost4_y>pac_y)
        {
            return DOWN;
        }
        else if (ghost4_x<pac_x && ghost4_y==pac_y)
        {
            return LEFT ;
        }
        else if(ghost4_x>pac_x && ghost4_y==pac_y)
        {
            return RIGHT ;
        }
        else if(ghost4_x<pac_x && ghost4_y<pac_y)
        {
            return DOWN ;
        }
        else if (ghost4_x<pac_x && ghost4_y>pac_y)
        {
            return DOWN;
        }
        else if (ghost4_x>pac_x && ghost4_y<pac_y)
        {
            return UP ;
        }
        else if (ghost4_x>pac_x && ghost4_y>pac_y)
        {
            return UP ;
        }

}


