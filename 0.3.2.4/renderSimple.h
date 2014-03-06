inline void renderFont(std::string msg, std::string fontFile, SDL_Color color, int fontSize, int x, int y, int wrapped)
{
    TTF_Font *font = NULL;                                                  //Create font
    font = TTF_OpenFont(fontFile.c_str(), fontSize);                        //Open font
    SDL_Surface *surf = NULL;
    //Render font to surface
    if( wrapped < 1 )
    {
        surf = TTF_RenderText_Solid( font, msg.c_str(), color);
    }
    else
    {
        surf = TTF_RenderText_Blended_Wrapped( font, msg.c_str(), color, wrapped );
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface( gRenderer, surf ); //Create texture from surface
    SDL_FreeSurface(surf);                                                  //Free original surface
    TTF_CloseFont(font);                                                    //Close font
    int w=0,h=0;                                                            //Initialise variables
    SDL_Rect rect;                                                          //Create texture rectangle
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);                          //Get texture data
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;                                                               //Set rectangle to texture parameters
    SDL_RenderCopy( gRenderer, texture, NULL, &rect );                      //Render the texture
    SDL_DestroyTexture(texture);                                            //Destroy the texture
}

inline int getRenderedWidth(std::string msg, std::string fontFile, int fontSize)   //Works out the width of a string in a certain font without rendering it
{
    SDL_Color color = {255,255,255};
    TTF_Font *font = NULL;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    SDL_Surface *surf = TTF_RenderText_Solid( font, msg.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface( gRenderer, surf );
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    int w=0,h=0;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    SDL_DestroyTexture(texture);

    return w-9; //Dodgy value
}

inline void renderFontCentered(std::string msg, std::string fontFile, SDL_Color color, int fontSize, int x, int y)
{
    TTF_Font *font = NULL;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    SDL_Surface *surf = NULL;
    surf = TTF_RenderText_Solid( font, msg.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface( gRenderer, surf );
    SDL_FreeSurface(surf);
    int w=0,h=0;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.w=w;
    rect.h=h;
    rect.x=(x-(rect.w)/2);
    rect.y=(y-(rect.h)/2);
    SDL_RenderCopy( gRenderer, texture, NULL, &rect );
    SDL_DestroyTexture(texture);
}

inline void renderTexture(SDL_Texture* texture, int x, int y, float ws, float hs)
{
    int w=0,h=0;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.x=x;rect.y=y;rect.h=(ceil(h*hs));rect.w=(ceil(w*ws));
    SDL_RenderCopy( gRenderer, texture, NULL, &rect);
}

inline void rotateTexture(SDL_Texture* texture, int x, int y, float ws, float hs, double angle )
{
    int w=0,h=0;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.x=x;rect.y=y;rect.h=(ceil(h*hs));rect.w=(ceil(w*ws));
    SDL_RenderCopyEx( gRenderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE );
}

inline void renderScreenCentre(SDL_Texture* texture, float s)
{
    int w=0,h=0;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    rect.w=w*s;rect.h=h*s;rect.x=(SCREEN_WIDTH/2)-(rect.w/2);rect.y=(SCREEN_HEIGHT/2)-(rect.h/2);
    SDL_RenderCopy( gRenderer, texture, NULL, &rect);
}
