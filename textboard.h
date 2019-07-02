#ifndef TEXTBOARD_H
#define TEXTBOARD_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class TextBoard : public QGraphicsItem
{
public:
    TextBoard();
    QRectF boundingRect() const;

    void setScore(int s);
    void setGameWon(bool _game_won);
    void setGameLost(bool _game_lost);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool game_won, game_lost, playing;
    int score;
    int x,y,w,h;
};

#endif // TEXTSTARTEND_H
