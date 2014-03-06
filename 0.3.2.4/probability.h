#include <cstdlib>
#include <iostream>

inline bool calculateChance( int win, int total )
{
    bool correct = false;
    for(int i=0;i<win;i++)
    {
        if( rand()%total == 0 )
        {
            correct = true;
        }
    }
    return correct;
}
inline void iterativeSeed(int rate, int tileIndex, int i, int ii, int layer,int it)
{

    for(int j=0,jj=-1;j<4;j++)
    {
    jj++;
       if( calculateChance(1,rate*2) and jj < it )
        {
            switch( j )
            {
                case 0:
                    if( ii != 0 )
                    {
                        world[layer][i][ii-1][0][0] = tileIndex;
                        iterativeSeed(rate,tileIndex,i,ii-1,layer,it-1);
                    }
                case 1:
                    if( i != 0 )
                    {
                        world[layer][i-1][ii][0][0] = tileIndex;
                        iterativeSeed(rate,tileIndex,i-1,ii,layer,it-1);
                    }
                case 2:
                    if( ii != 31 )
                    {
                        world[layer][i][ii+1][0][0] = tileIndex;
                        iterativeSeed(rate,tileIndex,i,ii+1,layer,it-1);
                    }
                case 3:
                    if( i != 31 )
                    {
                        world[layer][i+1][ii][0][0] = tileIndex;
                        iterativeSeed(rate,tileIndex,i+1,ii,layer,it-1);
                    }
            }
        }
       else
       {
           break;
       }
    }
}
