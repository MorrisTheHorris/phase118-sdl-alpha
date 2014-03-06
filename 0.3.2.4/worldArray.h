inline void sendToRender(int renderTopLeftX, int renderTopLeftY)
{
    for( int i=renderTopLeftY; i<(8+renderTopLeftY); i++)
    {
        for(int ii=renderTopLeftX; ii<(14+renderTopLeftX); ii++)
        {
            for(int iii=0; iii<worldLayers; iii++)
            {
                render[iii][ii-renderTopLeftX][i-renderTopLeftY] = world[iii][ii][i][0][0];
            }
        }
    }
}
