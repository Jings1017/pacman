#include "game_window.h"
#include <QApplication>
#include "enemy.h"
#include "enemy1.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game_window w;
    w.show();
    return a.exec();
}
