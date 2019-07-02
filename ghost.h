#ifndef GHOST_H
#define GHOST_H
#include <QGraphicsItem>
#include <QPainter>

class Ghost : public QGraphicsItem
{
public:
    Ghost();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void LoadGhostImages();
    void advance();

    void setGhost_X(int);
    void setGhost_Y(int);
    void setScared(bool option) {is_scared=option;}
    void setScaredWhite(bool option) {scared_white=option;}
    void setGhostDirection(int dir) {ghost_direction=dir;}
    void setNextGhostDirection(int dir) {ghost_next_direction=dir;}
    void setGhostColor(QString col);

    int getGhost_X() {return ghost_x;}
    int getGhost_Y() {return ghost_y;}
    int getGhostDirection() {return ghost_direction;}
    int getNextGhostDirection() {return ghost_next_direction;}
    bool getIsScared() {return is_scared;}
    bool getScaredWhite() {return scared_white;}
private:
    QPixmap ghost_pixmap;
    QPixmap ghost_scared_blue;
    QPixmap ghost_scared_white;
    QPixmap left1, left2, right1, right2;
    QPixmap up1, up2, down1, down2;
    QPixmap scaredblue, scaredblue1;
    QPixmap scaredwhite, scaredwhite1;

    bool is_scared;
    bool scared_white;
    bool hidden;

    int animestate;
    int animation_modify_factor;
    int ghost_x,ghost_y;
    int ghost_direction;
    int ghost_next_direction;
};

#endif // GHOST_H
