#include "dots.h"
#include "map.h"

Dots::Dots()
{
    Map referencemap;
    pacmanmapforreference = referencemap.getPaths();

    CreateDotsPositionsVector();
}

void Dots::CreateDotsPositionsVector()
{
    int x[17]={35,79,112,144,175,209,240,274,300,340,375,406,440,470,503,536,579};
    int y[19]={35,75,121,154,187,220,252,285,318,351,384,417,449,481,514,550,580,610,645};

    for(int i=0;i<17;++i)
    {
        for(int j=0;j<19;++j)
        {
                if(pacmanmapforreference.contains(QPoint(x[i],y[j])))
                {
                    if((x[i]==35||x[i]==579) && (y[j]==75||y[j]==514)) //skip the energizer
                    {
                        continue;
                    }
                    dots_positions.push_back(QPoint(x[i],y[j]));
                }
        }
    }

    // Create a new vector without the duplicates
    /*QVector<QPoint> unique_dotspositions;

    for (QVector<QPoint>::iterator iter = dots_positions.begin(); iter != dots_positions.end();++iter)
    {
        if(std::find(unique_dotspositions.begin(),unique_dotspositions.end(), *iter)==unique_dotspositions.end())
        {
            unique_dotspositions.push_back(*iter);
            dots_count++;
        }
    }
    std::swap( dots_positions, unique_dotspositions );*/
}
