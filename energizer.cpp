#include "energizer.h"
#include <QPoint>
#include <QVector>

Energizer::Energizer()
{
    QPoint energizer_position1 = QPoint(35,75);
    QPoint energizer_position2 = QPoint(579,75);
    QPoint energizer_position3 = QPoint(35,514);
    QPoint energizer_position4 = QPoint(579,514);

    energizer_positions.push_back(energizer_position1);
    energizer_positions.push_back(energizer_position2);
    energizer_positions.push_back(energizer_position3);
    energizer_positions.push_back(energizer_position4);
}

