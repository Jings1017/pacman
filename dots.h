#ifndef DOTS_H
#define DOTS_H

#include <QVector>
#include <QPoint>

class Dots
{
public:
    Dots();
    QVector<QPoint> getDotsPositions() {return dots_positions;}
    void CreateDotsPositionsVector();
private:
    QVector<QPoint> dots_positions;
    QVector<QPoint> pacmanmapforreference;
    int dots_count;
};

#endif // DOTS_H
