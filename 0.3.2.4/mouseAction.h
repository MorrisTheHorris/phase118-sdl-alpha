inline bool mouseOn(int mx, int my, int x, int y, int w, int h)
{
    bool on = true;
    if( mx < x) {on = false;}
    if( mx > (x+w)) {on = false;}
    if( my < y) {on = false;}
    if( my > (y+h)) {on = false;}
    return on;
}

inline void menuHovered(SDL_Color color, int option, std::string menu[])
{
    int x, y;
    SDL_GetMouseState(&x,&y);
    if( mouseOn(x,y,(RS*(630+(20*option))),(RS*(320+(50*option))),getRenderedWidth(menu[option], FONT, 48*RS),(RS*35)) )
    {
        renderFont(menu[option], FONT,color,(RS*48),(RS*(630+(20*option))),(RS*(320+(50*option))),0);
    }

    if( mouseOn(x,y,(RS*(630+(20*option))),(RS*(320+(50*option))),getRenderedWidth(menu[option], FONT, 48*RS),(RS*35)) )
    {
        if (!wasJustOnButton[option])
        {
            Mix_PlayChannel( -1, gHoverSFX, 0 );
        }
        wasJustOnButton[option] = true;
    }
    if( !mouseOn(x,y,(RS*(630+(20*option))),(RS*(320+(50*option))),getRenderedWidth(menu[option], FONT, 48*RS),(RS*35)) )
    {
        wasJustOnButton[option] = false;
    }
}

inline int xLocation(int tilesize, int excess)
{
    int x, y;
    SDL_GetMouseState(&x,&y);
    if( x < SCREEN_WIDTH-excess+RS*10 and x > excess)
    {
        return (x-excess)/tilesize;
    }
    else
    {
        return -1;
    }
}
inline int yLocation(int tilesize, int excess)
{
    int x, y;
    SDL_GetMouseState(&x,&y);
    if( y < SCREEN_HEIGHT-excess and y > excess)
    {
        return (y-excess)/tilesize;
    }
    else
    {
        return -1;
    }
}
