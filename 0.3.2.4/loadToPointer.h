SDL_Surface* loadSurface( std::string path )
{
    //Final optimised image
    SDL_Surface* optimisedSurface = NULL;

    //Load image
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Convert to screen format
        optimisedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, NULL );
        if ( optimisedSurface == NULL )
        {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Clear loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return optimisedSurface;
}

SDL_Texture* loadTexture( std::string path )
{
    //Final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError() );
        }
    }
    //Clear old surface
    SDL_FreeSurface( loadedSurface );

    return newTexture;
}
