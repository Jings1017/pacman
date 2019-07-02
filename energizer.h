#ifndef ENERGIZER_H
#define ENERGIZER_H

#include <QVector>
#include <QPoint>

class Energizer
{
public:
    Energizer();
    QVector<QPoint> getEnergizerPositions() {return energizer_positions;}
private:
    QVector<QPoint> energizer_positions;
};

#endif // ENERGIZER_H
