#ifndef DIALOG_H
#define DIALOG_H

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
#include "enemy.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "enemy4.h"

namespace Ui
{
    class Game_window;
}

class Game_window : public QDialog
{
    Q_OBJECT
public:
    explicit Game_window(QWidget *parent = 0);
    //void GenerateMap();
    //void PopulateMap();
    //void RespawnGhost();
    ~Game_window();
    void ShowScore();
    //void ShowHighScore(int score);
    void StartGame();
    void RestartGame();

    void GenerateMap();
    void GeneratePacman();
    void GenerateGhosts();

    void ResetMap();
    void ResetPacman();
    void ResetGhosts();

    void GhostMove1();
    void GhostMove2();
    void GhostMove3();
    void GhostMove4();

    void MoveGhostBack1();
    void MoveGhostBack2();
    void MoveGhostBack3();
    void MoveGhostBack4();

    void HideAll();
    void ClearDots();
    void PacmanMove();
    void CheckCollision();
    void EndGame(int win);   

public slots:
    void updater();
    void ghostupdater();

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Enemy *enemy1 = new Enemy1();
    Enemy *enemy2 = new Enemy2();
    Enemy *enemy3 = new Enemy3();
    Enemy *enemy4 = new Enemy4();

    int score;
    int dots_items_count;
    int collision;
    int scarestate;
    int start_timer;
    int high_score;

    bool ghostmoving1;
    bool ghostmoving2;
    bool ghostmoving3;
    bool ghostmoving4;

    bool ghoststart1;
    bool ghoststart2;
    bool ghoststart3;
    bool ghoststart4;

    bool start;
    bool playing;
    bool pause;
    bool scared;
    bool all_ghosts_started;
    bool ready_to_restart;

    Ui::Game_window *ui;
    QGraphicsScene scene;

    QTimer pacmantimer;
    QTimer ghoststimer;

    Map map;
    Dots dots;
    Energizer energizer;
    Pacman pacman;
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;

    TextBoard text_board;

    Sounds sounds;

    QVector<QPoint> energizer_positions;
    QVector<QPoint> dots_positions;

    QGraphicsPixmapItem *map_item;

    QVector<QGraphicsEllipseItem*> dots_items;
    QVector<QGraphicsEllipseItem*> energizer_items;

    QGraphicsTextItem *score_display;
    //QGraphicsTextItem *lives_display;

    QMediaPlayer *beginning_sound;
    QMediaPlayer *eat_sound1;
    QMediaPlayer *eat_sound2;
    QMediaPlayer *eat_ghost_sound;
    QMediaPlayer *pacman_death_sound;
};

#endif // DIALOG_H
