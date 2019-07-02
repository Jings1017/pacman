#include "map.h"

Map::Map()
{
    LoadPic();
    //hor

    //1
    CreatePoint( 35,  35, 274,  35);
    CreatePoint(340,  35, 579,  35);

    //3
    CreatePoint( 35, 121, 579, 121);

    //5
    CreatePoint( 35, 187, 144, 187);
    CreatePoint(209, 187, 274, 187);
    CreatePoint(340, 187, 406, 187);
    CreatePoint(470, 187, 579, 187);

    //7 mid
    CreatePoint(209, 252, 406, 252);

    //9 (mid)
    CreatePoint(  0, 318, 209, 318);
    CreatePoint(406, 318, 614, 318);

    //11
    CreatePoint(209, 384, 406, 384);

    //13
    CreatePoint( 35, 449, 274, 449);
    CreatePoint(340, 449, 579, 449);

    //15
    CreatePoint( 35, 514,  79, 514);
    CreatePoint(144, 514, 470, 514);
    CreatePoint(536, 514, 579, 514);

    //17
    CreatePoint( 35, 580, 144, 580);
    CreatePoint(209, 580, 274, 580);
    CreatePoint(340, 580, 406, 580);
    CreatePoint(470, 580, 579, 580);

    //19
    CreatePoint( 35, 645, 579, 645);

    //vert

    //1
    CreatePoint( 35,  35,  35, 187); // 5
    CreatePoint( 35, 449,  35, 514); // 3
    CreatePoint( 35, 580,  35, 645); // 3

    //2
    CreatePoint( 79, 514,  79, 580); // 3

    //3
    CreatePoint(144,  35, 144, 580); // 17

    //4
    CreatePoint(209, 121, 209, 187); // 3
    CreatePoint(209, 252, 209, 449); // 7
    CreatePoint(209, 514, 209, 580); // 3

    //5
    CreatePoint(274,  35, 274, 121); // 3
    CreatePoint(274, 187, 274, 252); // 3
    CreatePoint(274, 449, 274, 514); // 3
    CreatePoint(274, 580, 274, 645); // 3

    //6
    CreatePoint(340,  35, 340, 121); // 3
    CreatePoint(340, 187, 340, 252); // 3
    CreatePoint(340, 449, 340, 514); // 3
    CreatePoint(340, 580, 340, 645); // 3

    //7
    CreatePoint(406, 121, 406, 187); // 3
    CreatePoint(406, 252, 406, 449); // 7
    CreatePoint(406, 514, 406, 580); // 3

    //8
    CreatePoint(470,  35, 470, 580); // 17

    //9
    CreatePoint(536, 514, 536, 580); // 3

    //10
    CreatePoint(579,  35, 579, 187); // 5
    CreatePoint(579, 449, 579, 514); // 3
    CreatePoint(579, 580, 579, 645); // 3
}

QRectF Map::Bounding() const //sets map bounding rect which will be updated and redrawn every timer cycle
{
    return QRect(0,0,620,750);
}

void Map::CreatePoint(int x_begin, int y_begin, int x_end, int y_end)
{
    QPoint point;

    if (x_begin == x_end) //vertical
    {
        if (y_begin < y_end)
        {
            for (int y=y_begin ; y<=y_end ; ++y)
            {
                point.setX(x_begin);
                point.setY(y);

                if (! path.contains(point)) // check exist
                {
                    path.push_front(point);
                }
            }
        }

        else if(y_begin == y_end)
        {
                point.setX(x_begin);
                point.setY(y_begin);

                if (! path.contains(point))
                {
                    path.push_front(point);
                }
        }
    }

    if (y_begin == y_end) //horizontal
    {
        if (x_begin < x_end)
        {
            for (int x=x_begin ; x<=x_end ; ++x)
            {
                point.setX(x);
                point.setY(y_begin);

                if (! path.contains(point))
                {
                    path.push_front(point);
                }
            }
        }
        else if(x_begin == x_end)
        {
                point.setX(x_begin);
                point.setY(y_begin);

                if (! path.contains(point))
                {
                    path.push_front(point);
                }
        }
    }
}

bool Map::IsPointAvailable(QPoint point)
{
    for(int i=0 ; i<path.size() ; ++i )
    {
        if(path.at(i)==point)
        {
             return true;
        }
    }
    return false;
}

Map::~Map()
{
}

void Map::LoadPic()
{
    map_picture.load(":/images/pac_map.png");
}
