#include "game_window.h"
#include "ui_Game_window.h"
#include "map.h"
#include "energizer.h"
#include "enemy.h"
#include "enemy1.h"
#include <QGraphicsScene>
#include <QTime>
#include <QFile>
#include <QString>
#include <QThread>

#define LEFT  1
#define UP    2
#define DOWN  3
#define RIGHT 4

Game_window::Game_window(QWidget *parent) : QDialog(parent),ui(new Ui::Game_window)
{
    ui->setupUi(this);
    scene.setParent(this);
    ui->gameplay_area->setScene(&scene);
    ui->gameplay_area->setRenderHint(QPainter::Antialiasing);
    scene.setSceneRect(0,0,612,740);
    ui->gameplay_area->setSceneRect(scene.sceneRect());

    // map
    GenerateMap();
    // pacman
    GeneratePacman();
    // ghost
    GenerateGhosts();
    // score
    ShowScore();



    collision = 0;

    scene.addItem(&text_board);

    /*high_score_label = new QLabel(QString("BEST: %d").arg(1),this);
    high_score=0;
    QFile file("high_score.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        file.read((char*)&high_score,sizeof(high_score));
        file.close();
    }*/

    playing = false;
    ready_to_restart = false;
    pause = false;
    this->setFocus(Qt::ActiveWindowFocusReason);
}

Game_window::~Game_window()
{
    delete ui;
}

void Game_window::GenerateMap()
{
    map_item = scene.addPixmap(map.getMap_Background_Picture());
    energizer_positions = energizer.getEnergizerPositions();
    dots_positions = dots.getDotsPositions();

    for(int i=0;i<energizer_positions.size();++i)
    {
        energizer_items.push_back(scene.addEllipse(energizer_positions.at(i).x()-5,energizer_positions.at(i).y()-8,15,15,QPen(Qt::NoPen),QBrush(Qt::yellow)));
    }

    dots_items_count=dots_positions.size();

    for(int i=0;i<dots_positions.size();++i)
    {
        dots_items.push_back(scene.addEllipse(dots_positions.at(i).x(),dots_positions.at(i).y(),7,7,QPen(Qt::NoPen),QBrush(Qt::white)));
    }
}

void Game_window::GeneratePacman()
{
    start=false;

    pacman.setDirection(qrand()%4+1);

    pacman.setPac_X(310);
    pacman.setPac_Y(514);

    scene.addItem(&pacman);
}

void Game_window::GenerateGhosts()
{
    start_timer = 0;

    scared = false;

    scarestate = 0;

    ghost1.setScared(false);
    ghost2.setScared(false);
    ghost3.setScared(false);
    ghost4.setScared(false);

    ghost1.setGhost_X(307);
    ghost1.setGhost_Y(258);

    ghost2.setGhost_X(270);
    ghost2.setGhost_Y(318);

    ghost3.setGhost_X(344);
    ghost3.setGhost_Y(318);

    ghost4.setGhost_X(307);
    ghost4.setGhost_Y(318);

    ghost1.setGhostColor("orange");
    ghost2.setGhostColor("red");
    ghost3.setGhostColor("blue");
    ghost4.setGhostColor("pink");

    ghostmoving1=false;
    ghostmoving2=false;
    ghostmoving3=false;
    ghostmoving4=false;

    ghoststart1=false;
    ghoststart2=false;
    ghoststart3=false;
    ghoststart4=false;

    all_ghosts_started = false;

    scene.addItem(&ghost1);
    scene.addItem(&ghost2);
    scene.addItem(&ghost3);
    scene.addItem(&ghost4);
}

void Game_window::ShowScore()
{
    score=0;
    score_display = scene.addText("score:");
    score_display->setDefaultTextColor(Qt::white);
    score_display->setFont(QFont("Arial", 40));
    score_display->setPos(180,690);
}

/*void Game_window::ShowHighScore(int score)
{
    if(score > high_score)
    {
        high_score = score;
        high_score_label->setText(QString("BEST:%1").arg(score));

        QFile file("high_score.txt");
        file.open(QIODevice::WriteOnly);
        file.write((char*)&high_score,sizeof(high_score));
        file.close();
    }
}*/

void Game_window::StartGame()
{
    sounds.beginning_sound.play();

    text_board.hide();

    connect(&pacmantimer, SIGNAL(timeout()), this,SLOT(updater()));
    connect(&ghoststimer, SIGNAL(timeout()), this,SLOT(ghostupdater()));

    pacmantimer.start(10);
    ghoststimer.start(10);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void Game_window::RestartGame()
{
    ClearDots();

    pacman.show();
    ghost1.show();
    ghost2.show();
    ghost3.show();
    ghost4.show();

    GenerateMap();
    GeneratePacman();
    GenerateGhosts();

    ShowScore();

    sounds.beginning_sound.play();

    text_board.hide();

    pacmantimer.start(10);
    ghoststimer.start(10);
    this->setFocus(); //gives the keyboard input focus to this widget
}

void Game_window::ClearDots()
{
    energizer_items.clear();
    dots_items.clear();
    // release memory
    energizer_items.squeeze();
    dots_items.squeeze();
}

void Game_window::HideAll()
{
    // hide map
    map_item->hide();
    // hide score
    score_display->hide();
    // hide pacman
    pacman.hide();
    scene.removeItem(&pacman);
    // hide ghost
    ghost1.hide();
    ghost2.hide();
    ghost3.hide();
    ghost4.hide();
    scene.removeItem(&ghost1);
    scene.removeItem(&ghost2);
    scene.removeItem(&ghost3);
    scene.removeItem(&ghost4);
    // hide all dots
    for(int i=0; i<dots_items.size();++i)
    {
        dots_items.at(i)->hide();
    }

    for(int i=0; i<energizer_items.size();++i)
    {
        energizer_items.at(i)->hide();
    }
}

void Game_window::EndGame(int win)
{
    if(win==1)
    {
        HideAll();

        text_board.show();
        text_board.setScore(score);
        text_board.setGameWon(true);
        text_board.show();

        score=0;

        scene.update();
        playing = false;
        ready_to_restart = true;
    }

    else
    {
        HideAll();

        text_board.show();
        text_board.setScore(score);
        text_board.setGameLost(true);
        text_board.show();
        sounds.pacman_death_sound.play();
        score=0;

        scene.update();
        playing = false;
        ready_to_restart = true;
    }
}



void Game_window::MoveGhostBack1()
{
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost1_dir = ghost1.getGhostDirection();

    //enemy1->RectMove(ghost1_x,ghost1_dir);
    if(ghost1_x==307-50 || ghost1_x==307+50)
    {
        if(ghost1_dir==RIGHT)
        {
            ghost1_dir=LEFT;
        }
        else
        {
            ghost1_dir=RIGHT;
        }
    }

    if(ghost1_dir==RIGHT)
    {
        ghost1_x+=1;
    }
    else
    {
        ghost1_x-=1;
    }

    ghost1.setGhost_X(ghost1_x);
    ghost1.setGhost_Y(ghost1_y);
    ghost1.setGhostDirection(ghost1_dir);
}
void Game_window::MoveGhostBack2()
{
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost2_dir = ghost2.getGhostDirection();

    //enemy2->RectMove(ghost2_x,ghost2_dir);
    if(ghost2_x==307-50 || ghost2_x==307+50)
    {
        if(ghost2_dir==RIGHT)
        {
            ghost2_dir=LEFT;
        }
        else
        {
            ghost2_dir=RIGHT;
        }
    }
    if(ghost2_dir==RIGHT)
    {
        ghost2_x+=LEFT;
    }
    else
    {
        ghost2_x-=1;
    }

    ghost2.setGhost_X(ghost2_x);
    ghost2.setGhost_Y(ghost2_y);
    ghost2.setGhostDirection(ghost2_dir);
}
void Game_window::MoveGhostBack3()
{
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost3_dir = ghost3.getGhostDirection();

    //enemy3->RectMove(ghost3_x,ghost3_dir);
    if(ghost3_x==307-50 || ghost3_x==307+50)
    {
        if(ghost3_dir==RIGHT)
        {
            ghost3_dir=LEFT;
        }
        else
        {
            ghost3_dir=RIGHT;
        }
    }
    if(ghost3_dir==RIGHT)
    {
        ghost3_x+=1;
    }
    else
    {
        ghost3_x-=1;
    }

    ghost3.setGhost_X(ghost3_x);
    ghost3.setGhost_Y(ghost3_y);
    ghost3.setGhostDirection(ghost3_dir);
}
void Game_window::MoveGhostBack4()
{
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();
    int ghost4_dir = ghost4.getGhostDirection();

    //enemy4->RectMove(ghost4_x,ghost4_dir);
    if(ghost4_x==307-50 || ghost4_x==307+50)
    {
        if(ghost4_dir==RIGHT)
        {
            ghost4_dir=LEFT;
        }
        else
        {
            ghost4_dir=RIGHT;
        }
    }
    if(ghost4_dir==RIGHT)
    {
        ghost4_x+=1;
    }
    else
    {
        ghost4_x-=1;
    }

    ghost4.setGhost_X(ghost4_x);
    ghost4.setGhost_Y(ghost4_y);
    ghost4.setGhostDirection(ghost4_dir);
}

void Game_window::keyPressEvent(QKeyEvent *event) //supports pacman movement using WSAD and directional keys
{
    int pacman_nextdir = pacman.getNextDirection();

    switch(event->key())
    {
    case Qt::Key_Left:
        pacman_nextdir=LEFT;
        break;
    case Qt::Key_A:
        pacman_nextdir=LEFT;
        break;

    case Qt::Key_Right:
        pacman_nextdir=RIGHT;
        break;
    case Qt::Key_D:
        pacman_nextdir=RIGHT;
        break;

    case Qt::Key_Down:
        pacman_nextdir=DOWN;
        break;
    case Qt::Key_S:
        pacman_nextdir=DOWN;
        break;

    case Qt::Key_Up:
        pacman_nextdir=UP;
        break;
    case Qt::Key_W:
        pacman_nextdir=UP;
        break;

    case Qt::Key_1:
        pacmantimer.start(10);
        ghoststimer.start(10);
        break;
    case Qt::Key_2:
        pacmantimer.start(7);
        ghoststimer.start(7);
        break;
    case Qt::Key_3:
        pacmantimer.start(5);
        ghoststimer.start(5);
        break;
    case Qt::Key_4:
        pacmantimer.start(3);
        ghoststimer.start(3);
        break;
    case Qt::Key_5:
        pacmantimer.start(1);
        ghoststimer.start(1);
        break;


    case Qt::Key_Space:
        if(!playing && ready_to_restart == false)
        {
            playing = true;
            StartGame();
        }
        if(!playing && ready_to_restart == true)
        {
            ready_to_restart = false;
            playing = true;
            RestartGame();
        }
        break;

    case Qt::Key_Z:
        if(playing && pause == false)
        {
            pause = true;
            pacmantimer.stop();
            ghoststimer.stop();
        }
        else if(playing && pause==true)
        {
            pause = false;
            pacmantimer.start(10);
            ghoststimer.start(10);
        }
        break;
    case Qt::Key_X:
        QTime tt;
        tt.start();
        while(tt.elapsed()<5000);
        break;
    //default:
      //  break;
    }
    pacman.setNextDirection(pacman_nextdir);
}
// let ghost back to StartRect and out
void Game_window::CheckCollision()
{
    if(pacman.collidesWithItem(&ghost1) ||
       pacman.collidesWithItem(&ghost2) ||
       pacman.collidesWithItem(&ghost3) ||
       pacman.collidesWithItem(&ghost4))
    {
        if(pacman.collidesWithItem(&ghost1) && ghost1.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score +=200;
            score_display->setPlainText("score: " + QString::number(score));
            ghost1.setGhost_X(307);
            ghost1.setGhost_Y(252);
            ghost1.setScared(false);
        }
        else if(pacman.collidesWithItem(&ghost2) && ghost2.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("score: " + QString::number(score));
            ghost2.setGhost_X(307);
            ghost2.setGhost_Y(252);
            ghost2.setScared(false);
        }
        else if(pacman.collidesWithItem(&ghost3) && ghost3.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("score: " + QString::number(score));
            ghost3.setGhost_X(307);
            ghost3.setGhost_Y(252);
            ghost3.setScared(false);
        }
        else if(pacman.collidesWithItem(&ghost4) && ghost4.getIsScared())
        {
            sounds.eat_ghost_sound.play();
            score+=200;
            score_display->setPlainText("score: " + QString::number(score));
            ghost4.setGhost_X(307);
            ghost4.setGhost_Y(252);
            ghost4.setScared(false);
        }
        else // touch the ghost which is normal
        {
            pacmantimer.stop();
            ghoststimer.stop();
            EndGame(0);
        }
    }
}

void Game_window::updater()
{
    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();

    if(collision >= 500)
        CheckCollision();
    else
        collision++;

    PacmanMove();


    for(int i=0;i<dots_positions.size();++i)
    {
        if(pac_x==dots_positions.at(i).x() && pac_y==dots_positions.at(i).y())
        {
            dots_positions.remove(i);
            dots_items.at(i)->hide();
            dots_items.remove(i);

            if(sounds.eat_sound1.state()==QMediaPlayer::StoppedState)
            {
                sounds.eat_sound1.play();
            }

            if(sounds.eat_sound1.state()==QMediaPlayer::PlayingState)
            {
                sounds.eat_sound1.play();
            }

            score = score + 10 ;
            score_display->setPlainText("score: " + QString::number(score));

            dots_items_count--;
        }
    }

    for(int i=0;i<energizer_positions.size();++i)
    {
        if(pac_x==energizer_positions.at(i).x() && pac_y==energizer_positions.at(i).y())
        {
            energizer_positions.remove(i);
            energizer_items.at(i)->hide();
            energizer_items.remove(i);

            score += 200;
            score_display->setPlainText("Score: " + QString::number(score));

            scarestate = 0;

            ghost1.setScared(true);
            ghost2.setScared(true);
            ghost3.setScared(true);
            ghost4.setScared(true);

            scared=true;

            score_display->setPlainText("Score: " + QString::number(score));
        }
    }
    // eat all balls
    if(dots_items_count==0)
    {
        pacmantimer.stop();
        ghoststimer.stop();
        EndGame(1);
    }

    if(scared)
    {
        scarestate+=1;

        if(scarestate==1)
        {
            ghoststimer.setInterval(20); // slow speed
        }

        if(scarestate==750)
        {
            ghost1.setScaredWhite(true);
            ghost2.setScaredWhite(true);
            ghost3.setScaredWhite(true);
            ghost4.setScaredWhite(true);
        }

        if(scarestate==1000)
        {
            scared=false;
            ghost1.setScared(false);
            ghost2.setScared(false);
            ghost3.setScared(false);
            ghost4.setScared(false);

            ghost1.setScaredWhite(false);
            ghost2.setScaredWhite(false);
            ghost3.setScaredWhite(false);
            ghost4.setScaredWhite(false);

            scarestate = 0;
            ghoststimer.setInterval(10);
        }
    }

    pacman.advance();
    ghost1.advance();
    ghost2.advance();
    ghost3.advance();
    ghost4.advance();

    scene.update(scene.sceneRect());
}

void Game_window::ghostupdater()
{
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();

    if(all_ghosts_started)
    {
        GhostMove1();
        GhostMove2();
        GhostMove3();
        GhostMove4();
    }
    else
    {
        if(!ghoststart1)
            MoveGhostBack1();
        else
            GhostMove1();

        if(!ghoststart2)
            MoveGhostBack2();
        else
            GhostMove2();

        if(!ghoststart3)
            MoveGhostBack3();
        else
            GhostMove3();

        if(!ghoststart4)
            MoveGhostBack4();
        else
            GhostMove4();


        if(ghost1_x==300 || ghost2_x==300 || ghost3_x==300 || ghost4_x==300)
        {
            start_timer++;
        }

        for(int i=0;i<dots_positions.size();++i)
        {
            if(ghost1_x==dots_positions.at(i).x() && ghost1_y==dots_positions.at(i).y())
            {
                dots_positions.remove(i);
                dots_items.at(i)->hide();
                dots_items.remove(i);

                score = score + 0 ;
                score_display->setPlainText("score: " + QString::number(score));

                dots_items_count--;
            }
        }

        if(start_timer>=0) // ghost 1 starts
        {
            QPoint p1;
            if(ghost1_x>307)
            {
                ghost1_x-=1;
            }
            else if(ghost1_x<307)
            {
                ghost1_x+=1;
            }

            if(!ghoststart1)
            {
                ghost1_y-=1;
                ghost1.setGhost_X(ghost1_x);
                ghost1.setGhost_Y(ghost1_y);
                p1.setX(ghost1_x);
                p1.setY(ghost1_y);
                if(map.getPaths().contains(p1))
                {
                    ghoststart1=true;
                }
            }
        }



        if(start_timer>=4) // ghost 2 starts
        {
            QPoint p2;
            if(ghost2_x>307)
            {
                ghost2_x-=1;
            }
            else if(ghost2_x<307)
            {
                ghost2_x+=1;
            }

            if(!ghoststart2)
            {
                ghost2_y-=1;
                ghost2.setGhost_X(ghost2_x);
                ghost2.setGhost_Y(ghost2_y);
                p2.setX(ghost2_x);
                p2.setY(ghost2_y);
                if(map.getPaths().contains(p2))
                {
                    ghoststart2=true;
                }
            }
        }

        if(start_timer>=8) // ghost 3 starts
        {
            QPoint p3;
            if(ghost3_x>307)
            {
                ghost3_x-=1;
            }
            else if(ghost3_x<307)
            {
                ghost3_x+=1;
            }

            if(!ghoststart3)
            {
                ghost3_y-=1;
                ghost3.setGhost_X(ghost3_x);
                ghost3.setGhost_Y(ghost3_y);
                p3.setX(ghost3_x);
                p3.setY(ghost3_y);
                if(map.getPaths().contains(p3))
                {
                    ghoststart3=true;
                }
            }
        }

        if(start_timer>=12) // ghost 4 starts
        {
            QPoint p4;
            if(ghost4_x>307)
            {
                ghost4_x-=1;
            }
            else if(ghost4_x<307)
            {
                ghost4_x+=1;
            }

            if(!ghoststart4)
            {
                ghost4_y-=1;
                ghost4.setGhost_X(ghost4_x);
                ghost4.setGhost_Y(ghost4_y);
                p4.setX(ghost4_x);
                p4.setY(ghost4_y);
                if(map.getPaths().contains(p4))
                {
                    ghoststart4=true;
                }
            }
        }

        if(ghoststart1 && ghoststart2 && ghoststart3 && ghoststart4)
            all_ghosts_started=true;
    }
    for(int i=0;i<dots_positions.size();++i)
    {
        if(ghost1_x==dots_positions.at(i).x() && ghost1_y==dots_positions.at(i).y())
        {
            dots_positions.remove(i);
            dots_items.at(i)->hide();
            dots_items.remove(i);

            score = score + 0 ;
            score_display->setPlainText("score: " + QString::number(score));

            dots_items_count--;
        }
    }
}

void Game_window::PacmanMove()
{
    QPoint point;

    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();
    int direction = pacman.getDirection();
    int nextdirection = pacman.getNextDirection();

    if(nextdirection != direction)
    {
        switch(nextdirection)
        {
        case LEFT:
            point.setX(pac_x-1);
            point.setY(pac_y);

            if(map.IsPointAvailable(point))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case UP:
            point.setX(pac_x);
            point.setY(pac_y-1);
            if(map.IsPointAvailable(point))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case DOWN:
            point.setX(pac_x);
            point.setY(pac_y+1);
            if(map.IsPointAvailable(point))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;

        case RIGHT:
            point.setX(pac_x+1);
            point.setY(pac_y);
            if(map.IsPointAvailable(point))
            {
                direction=nextdirection;
                nextdirection=0;
            }
            break;
        }
    }

    switch(direction)
    {
    case LEFT:
        point.setX(pac_x-1);
        point.setY(pac_y);
        pacman.setDirection(direction);

        if(map.IsPointAvailable(point))
        {
            pac_x = pac_x - 1;
        }

        break;

    case UP:
        point.setX(pac_x);
        point.setY(pac_y-1);
        pacman.setDirection(direction);

        if(map.IsPointAvailable(point))
        {
            pac_y= pac_y - 1;
        }

        break;

    case DOWN:
        point.setX(pac_x);
        point.setY(pac_y+1);
        pacman.setDirection(direction);

        if(map.IsPointAvailable(point))
        {
            pac_y= pac_y + 1;
        }

        break;

    case RIGHT:
        point.setX(pac_x+1);
        point.setY(pac_y);
        pacman.setDirection(direction);

        if(map.IsPointAvailable(point))
        {
            pac_x = pac_x + 1;
        }

        break;
    }

    // can throu from right to left
    if(pac_x==0 && pac_y==318) //teleportation when reached left boundary of middle horizontal line
    {
        pac_x=613;
    }

    if(pac_x==614 && pac_y==318) //teleportation when reached right boundary of middle horizontal line
    {
        pac_x=1;
    }

    pacman.setPac_X(pac_x);
    pacman.setPac_Y(pac_y);
}

void Game_window::GhostMove1()
{
    QPoint p;

    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();
    int ghost1_x = ghost1.getGhost_X();
    int ghost1_y = ghost1.getGhost_Y();
    int ghost1_dir = ghost1.getGhostDirection();
    int nextghost1_dir = ghost1.getNextGhostDirection();

    if(!ghostmoving1)
    {
        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        ghost1_dir=(qrand()%4)+1;
    }
    else
    {
        if(scared==false)
            nextghost1_dir = enemy1->move(pac_x,pac_y,ghost1_x,ghost1_y);
        else
            nextghost1_dir = enemy1->scaredmove(pac_x,pac_y,ghost1_x,ghost1_y);
    }
    // turn
    if(nextghost1_dir != ghost1_dir)
    {
        switch(nextghost1_dir)
        {
        case LEFT:
            p.setX(ghost1_x-1);
            p.setY(ghost1_y);

            if(map.IsPointAvailable(p))
            {
                ghost1_dir = nextghost1_dir;
                nextghost1_dir = 0;
            }

            break;

        case RIGHT:
            p.setX(ghost1_x+1);
            p.setY(ghost1_y);
            if(map.IsPointAvailable(p))
            {
                ghost1_dir = nextghost1_dir;
                nextghost1_dir = 0 ;
            }

            break;

        case DOWN:
            p.setX(ghost1_x);
            p.setY(ghost1_y+1);
            if(map.IsPointAvailable(p))
            {
                ghost1_dir = nextghost1_dir;
                nextghost1_dir = 0;
            }

            break;

        case UP:
            p.setX(ghost1_x);
            p.setY(ghost1_y-1);
            if(map.IsPointAvailable(p))
            {
                ghost1_dir = nextghost1_dir;
                nextghost1_dir = 0;
            }

            break;
        }
    }

    switch(ghost1_dir)
    {
    case LEFT:
        p.setX(ghost1_x-1);
        p.setY(ghost1_y);
        ghost1.setGhostDirection(ghost1_dir);

        if(map.IsPointAvailable(p))
        {
            ghost1_x = ghost1_x -1 ;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;

    case RIGHT:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x+1);
        p.setY(ghost1_y);
        if(map.IsPointAvailable(p))
        {
            ghost1_x = ghost1_x +1 ;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;

    case DOWN:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x);
        p.setY(ghost1_y+1);
        if(map.IsPointAvailable(p))
        {
            ghost1_y = ghost1_y +1 ;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;
    case UP:
        ghost1.setGhostDirection(ghost1_dir);
        p.setX(ghost1_x);
        p.setY(ghost1_y-1);
        if(map.IsPointAvailable(p))
        {
            ghost1_y =  ghost1_y -1 ;
            ghostmoving1=true;
        }
        else
        {
            ghostmoving1=false;
        }

        break;
    }

    if(ghost1_x<=0)
    {
        ghost1_x=613;
        ghost1_y=318;
    }
    else if(ghost1_x>=614)
    {
        ghost1_x=1;
        ghost1_y=318;
    }

    ghost1.setGhost_X(ghost1_x);
    ghost1.setGhost_Y(ghost1_y);
    ghost1.setNextGhostDirection(nextghost1_dir);
}
void Game_window::GhostMove2()
{
    QPoint p;

    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();
    int ghost2_x = ghost2.getGhost_X();
    int ghost2_y = ghost2.getGhost_Y();
    int ghost2_dir = ghost2.getGhostDirection();
    int nextghost2_dir = ghost2.getNextGhostDirection();

    if(!ghostmoving2)
    {
        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        ghost2_dir=(qrand()%4)+1;
    }
    else
    {
        if(scared==false)
            nextghost2_dir = enemy2->move(pac_x,pac_y,ghost2_x,ghost2_y);
        else
            nextghost2_dir = enemy2->scaredmove(pac_x,pac_y,ghost2_x,ghost2_y);
    }

    if(nextghost2_dir!=ghost2_dir)
    {
        switch(nextghost2_dir)
        {
        case LEFT:
            p.setX(ghost2_x-1);
            p.setY(ghost2_y);

            if(map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;

        case RIGHT:
            p.setX(ghost2_x+1);
            p.setY(ghost2_y);
            if(map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;
        case DOWN:
            p.setX(ghost2_x);
            p.setY(ghost2_y+1);
            if(map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }

            break;
        case UP:
            p.setX(ghost2_x);
            p.setY(ghost2_y-1);
            if(map.IsPointAvailable(p))
            {
                ghost2_dir=nextghost2_dir;
                nextghost2_dir=0;
            }
            break;
        }
    }

    switch(ghost2_dir)
    {
    case LEFT:
        p.setX(ghost2_x-1);
        p.setY(ghost2_y);
        ghost2.setGhostDirection(ghost2_dir);

        if(map.IsPointAvailable(p))
        {
            ghost2_x-=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;

    case RIGHT:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x+1);
        p.setY(ghost2_y);
        if(map.IsPointAvailable(p))
        {
            ghost2_x+=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    case DOWN:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x);
        p.setY(ghost2_y+1);
        if(map.IsPointAvailable(p))
        {
            ghost2_y+=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    case UP:
        ghost2.setGhostDirection(ghost2_dir);
        p.setX(ghost2_x);
        p.setY(ghost2_y-1);
        if(map.IsPointAvailable(p))
        {
            ghost2_y-=1;
            ghostmoving2=true;
        }
        else
        {
            ghostmoving2=false;
        }

        break;
    }

    if(ghost2_x<=0)
    {
        ghost2_x=613;
        ghost2_y=318;
    }
    else if(ghost2_x>=614)
    {
        ghost2_x=1;
        ghost2_y=318;
    }

    ghost2.setGhost_X(ghost2_x);
    ghost2.setGhost_Y(ghost2_y);
    ghost2.setNextGhostDirection(nextghost2_dir);
}
void Game_window::GhostMove3()
{
    QPoint p;

    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();
    int ghost3_x = ghost3.getGhost_X();
    int ghost3_y = ghost3.getGhost_Y();
    int ghost3_dir = ghost3.getGhostDirection();
    int nextghost3_dir = ghost3.getNextGhostDirection();

    if(!ghostmoving3)
    {
        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        ghost3_dir=(qrand()%4)+1;
    }
    else
    {
        if(scared==false)
            nextghost3_dir = enemy3->move(pac_x,pac_y,ghost3_x,ghost3_y);
        else
            nextghost3_dir = enemy3->scaredmove(pac_x,pac_y,ghost3_x,ghost3_y);
    }

    if(nextghost3_dir!=ghost3_dir)
    {
        switch(nextghost3_dir)
        {
        case LEFT:
            p.setX(ghost3_x-1);
            p.setY(ghost3_y);

            if(map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;

            }

            break;

        case RIGHT:
            p.setX(ghost3_x+1);
            p.setY(ghost3_y);
            if(map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }

            break;
        case DOWN:
            p.setX(ghost3_x);
            p.setY(ghost3_y+1);
            if(map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }

            break;
        case UP:
            p.setX(ghost3_x);
            p.setY(ghost3_y-1);
            if(map.IsPointAvailable(p))
            {
                ghost3_dir=nextghost3_dir;
                nextghost3_dir=0;
            }
            break;
        }

    }
    switch(ghost3_dir)
    {
    case LEFT:
        p.setX(ghost3_x-1);
        p.setY(ghost3_y);
        ghost3.setGhostDirection(ghost3_dir);

        if(map.IsPointAvailable(p))
        {
            ghost3_x-=1;
            ghostmoving3=true;

        }
        else
        {
            ghostmoving3=false;
        }

        break;

    case RIGHT:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x+1);
        p.setY(ghost3_y);
        if(map.IsPointAvailable(p))
        {
            ghost3_x+=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }

        break;
    case DOWN:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x);
        p.setY(ghost3_y+1);
        if(map.IsPointAvailable(p))
        {
            ghost3_y+=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }

        break;
    case UP:
        ghost3.setGhostDirection(ghost3_dir);
        p.setX(ghost3_x);
        p.setY(ghost3_y-1);
        if(map.IsPointAvailable(p))
        {
            ghost3_y-=1;
            ghostmoving3=true;
        }
        else
        {
            ghostmoving3=false;
        }
        break;
    }


    if(ghost3_x<=0)
    {
        ghost3_x=613;
        ghost3_y=318;
    }
    else if(ghost3_x>=614)
    {
        ghost3_x=1;
        ghost3_y=318;
    }

    ghost3.setGhost_X(ghost3_x);
    ghost3.setGhost_Y(ghost3_y);
    ghost3.setNextGhostDirection(nextghost3_dir);
}
void Game_window::GhostMove4()
{
    QPoint p;

    int pac_x = pacman.getPac_X();
    int pac_y = pacman.getPac_Y();
    int ghost4_x = ghost4.getGhost_X();
    int ghost4_y = ghost4.getGhost_Y();
    int ghost4_dir = ghost4.getGhostDirection();
    int nextghost4_dir = ghost4.getNextGhostDirection();

    if(!ghostmoving4)
    {
        QTime t;
        t = QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        ghost4_dir=(qrand()%4)+1;
    }
    else
    {
        if(scared==false)
            nextghost4_dir = enemy4->move(pac_x,pac_y,ghost4_x,ghost4_y);
        else
            nextghost4_dir = enemy4->scaredmove(pac_x,pac_y,ghost4_x,ghost4_y);
    }

    if(nextghost4_dir!=ghost4_dir)
    {
        switch(nextghost4_dir)
        {
        case LEFT:
            p.setX(ghost4_x-1);
            p.setY(ghost4_y);

            if(map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;

        case RIGHT:
            p.setX(ghost4_x+1);
            p.setY(ghost4_y);
            if(map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        case DOWN:
            p.setX(ghost4_x);
            p.setY(ghost4_y+1);
            if(map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        case UP:
            p.setX(ghost4_x);
            p.setY(ghost4_y-1);
            if(map.IsPointAvailable(p))
            {
                ghost4_dir=nextghost4_dir;
                nextghost4_dir=0;
            }

            break;
        }

    }
    switch(ghost4_dir)
    {
    case LEFT:
        p.setX(ghost4_x-1);
        p.setY(ghost4_y);
        ghost4.setGhostDirection(ghost4_dir);

        if(map.IsPointAvailable(p))
        {
            ghost4_x-=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;

    case RIGHT:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x+1);
        p.setY(ghost4_y);
        if(map.IsPointAvailable(p))
        {
            ghost4_x+=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;
    case DOWN:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x);
        p.setY(ghost4_y+1);
        if(map.IsPointAvailable(p))
        {
            ghost4_y+=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }

        break;
    case UP:
        ghost4.setGhostDirection(ghost4_dir);
        p.setX(ghost4_x);
        p.setY(ghost4_y-1);
        if(map.IsPointAvailable(p))
        {
            ghost4_y-=1;
            ghostmoving4=true;
        }
        else
        {
            ghostmoving4=false;
        }
        break;
    }

    if(ghost4_x<=0)
    {
        ghost4_x=613;
        ghost4_y=318;
    }
    else if(ghost4_x>=614)
    {
        ghost4_x=1;
        ghost4_y=318;
    }
    ghost4.setGhost_X(ghost4_x);
    ghost4.setGhost_Y(ghost4_y);
    ghost4.setNextGhostDirection(nextghost4_dir);
}
