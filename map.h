#ifndef MAP_H
#define MAP_H

#include <QVector>
#include <QPixmap>

class Map
{
public:
    Map();
    ~Map();
    void CreatePoint(int x_begin, int y_begin, int x_end, int y_end);
    bool IsPointAvailable(QPoint);
    void LoadPic();
    QRectF Bounding() const;
    QPixmap getMap_Background_Picture() {return map_picture;}
    QVector<QPoint> getPaths() {return path;}
private:
    QVector<QPoint> path;
    QPixmap map_picture;
};

#endif // MAP_H
