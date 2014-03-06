void renderMenu(std::string menu[])
{
    for (int i=0; i<4; i++)
    {
        //Render disabled items in orange
        if( menu == menuItems || menu == demoMenuItems || menu == demoErraticMenuItems)
        {
            if( i == 1 || i == 2 )
            {
                renderFont(menu[i], FONT,colorD,RS*48,RS*(630+(20*i)),RS*(320+(50*i)),0);
            }
            else
            {
                renderFont(menu[i], FONT,color,RS*48,RS*(630+(20*i)),RS*(320+(50*i)),0);
            }
        }
        else
        {
            renderFont(menu[i], FONT,color,RS*48,RS*(630+(20*i)),RS*(320+(50*i)),0);
        }

        //Selection
        menuHovered(colorS,i,menu);

    }
    //Render other links
    renderFont("Credits",FONT,color,16*RS,SCREEN_WIDTH-((getRenderedWidth("Credits",FONT,16*RS)+150)*RS),8*RS,0);
    int x, y;
    SDL_GetMouseState(&x,&y);
    if( mouseOn(x,y,SCREEN_WIDTH-((getRenderedWidth("Credits",FONT,16*RS)+150)*RS),8*RS,getRenderedWidth("Credits",FONT,16*RS),16*RS))
    {
        renderFont("Credits",FONT,colorS,16*RS,SCREEN_WIDTH-((getRenderedWidth("Credits",FONT,16*RS)+150)*RS),8*RS,0);
    }
}

void renderTitleScreen()
{
    renderTexture( gTexture,0,0,8*RS,8*RS );
    renderFont("Phase 118",FONT,color,100*RS,465*RS,104*RS,0);
    renderFont(CurrentVersion,FONT,color,16*RS,8*RS,SCREEN_HEIGHT-(16*RS),0);
    renderFont("| Rising Voxel Games",FONT,color,16*RS,SCREEN_WIDTH-(170*RS),8*RS,0);
}

void renderCredits(int y)
{
    int speed = 1;

    for( int i = 0; i < 10; i++ )
    {
        if( i == 0)
        {
            renderFontCentered(credits[i],FONT,colorS,128*RS,SCREEN_WIDTH/2,y+(i*64*RS));
        }
        else if(i == 1 || i == 3 || i == 6 || i == 9 || i == 10)
        {
            renderFontCentered(credits[i],FONT,colorB,48*RS,SCREEN_WIDTH/2,y+(i*64*RS));
        }
        else
        {
            renderFontCentered(credits[i],FONT,colorB,36*RS,SCREEN_WIDTH/2,y+(i*64*RS));
        }

    }
}
