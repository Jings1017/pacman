#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
public:
    virtual ~Enemy()=0;
    virtual int move(int, int, int, int)=0;
    virtual int scaredmove(int, int, int, int)=0;
};

#endif // ENEMY_H
