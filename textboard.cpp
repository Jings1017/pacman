#include "textboard.h"

TextBoard::TextBoard()
{
    game_won=false;
    game_lost=false;
    playing=false;
    score=0;

    w=600;
    h=200;
    x=614/2-w/2;
    y=714/2-h/2;

}

QRectF TextBoard::boundingRect() const
{
    return QRect(x, y, w, h);
}

void TextBoard::setScore(int s)
{
    this -> score = s;
}

void TextBoard::setGameWon(bool _game_won)
{
    this -> game_won = _game_won;
}

void TextBoard::setGameLost(bool _game_lost)
{
    this -> game_lost = _game_lost;
}

void TextBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QFont font = painter->font();
    font.setPointSize (30);
    painter->setFont(font);

    if(!playing)
    {
        if(game_won)
        {
            painter->setPen(Qt::yellow);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"YOU WON");
            painter->drawText(boundingRect(),Qt::AlignCenter, "SCORE : "+QString::number(score));
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else if(game_lost)
        {
            painter->setPen(Qt::red);
            painter->drawText(boundingRect(),Qt::AlignTop | Qt::AlignHCenter,"GAME OVER");
            painter->drawText(boundingRect(),Qt::AlignCenter, "SCORE : "+QString::number(score));
            painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"PRESS SPACE TO RESTART");
        }
        else
        {
            painter->setPen(Qt::yellow);
            painter->drawText(boundingRect(),Qt::AlignCenter, "PRESS SPACE TO START");
            //painter->drawText(boundingRect(),Qt::AlignBottom | Qt::AlignHCenter,"SELECT LEVEL BY KEY 1~5");
        }
    }
}
