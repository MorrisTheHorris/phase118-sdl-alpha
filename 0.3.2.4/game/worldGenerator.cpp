#include "worldGenerator.h"
#include "../include.h"
#include "../probability.h"
#include "../worldArray.h"

worldGenerator::worldGenerator()
{
    //Seed the random world generator
    srand (time(NULL));
}

void worldGenerator::createWorld(int oceanRarity, int grassRarity, int treeRarity)
{
    //Set all to dirt and blank
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            for(int iii=1;iii<worldLayers;iii++)
            {
                world[iii][i][ii][0][0] = 0;
            }
            world[0][i][ii][0][0] = 1;
        }
    }

    //Seed grass
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            if( calculateChance(1,grassRarity) )
            {
                iterativeSeed(1,0,i,ii,0,5);
            }
        }
    }

    //Seed ocean
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            if( calculateChance(1,oceanRarity) )
            {
                iterativeSeed(1,2,i,ii,0,5);
            }
        }
    }
    //Seed forests
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            if( world[0][i][ii][0][0] == 0 )
            {
                if( calculateChance(1,treeRarity) )
                {
                    iterativeSeed(1,rand()%4 + 1,i,ii,1,2);
                }
            }
        }
    }
    //Remove stuff from oceans
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            if( world[0][i][ii][0][0] == 2 and world[1][i][ii][0][0] != 0 )
            {
                world[1][i][ii][0][0] = 0;
            }
        }
    }
    //Put the sand around oceans
    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            if( world[0][i][ii][0][0] != 2 ) //if tile is not water
            {
                if( i > 0 and i < 31 and ii > 0 and ii < 31) //if tile is not on edge of map cos that would break things and im lazy
                {
                    if( world[0][i+1][ii][0][0] == 2 or world[0][i-1][ii][0][0] == 2 or world[0][i][ii+1][0][0] == 2 or world[0][i][ii-1][0][0] == 2)
                    {
                        world[0][i][ii][0][0] = 3;
                    }
                }
            }
        }
    }

    //Data creation
    bool naturalHelium = false;

    for(int i=0; i<32; i++)
    {
        for(int ii=0; ii<32; ii++)
        {
            for(int d=0; d<2; d++)
            {
                switch(d+1)// All yields are percentages out of 100
                {
                case 1: // H yield
                    //if( calculateChance(1,10) )
                    //{
                        data[0][i][ii] = rand()%101;
                    //}
                case 2: // He yield
                    {
                        if( !naturalHelium )
                        {
                            data[1][i][ii] = 0;
                        }
                        else
                        {
                            if( calculateChance(1,30) )
                            {
                                data[1][i][ii] = rand()%101;
                            }
                        }
                    }
                //default: //Other data is zero
                    //data[d][i][ii] = 0;
                }
            }
        }
    }

}

worldGenerator::~worldGenerator()
{
    //dtor
}
