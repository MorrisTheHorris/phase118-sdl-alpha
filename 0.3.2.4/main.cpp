/** PHASE 118
 *  DEVELOPED USING SDL 2.0 and C++11
 *  COPYRIGHT 2014
 *  HARRISON SCOTT
 */
#include "include.h"
#include "globals.h"
#include "functions.h"

//Execute main functions
bool init();
bool loadMedia();
void close();

//Starts SDL and creates window
bool init()
{
    bool success = true;

    //Initialise SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialise! SDL_Error:%s\n", SDL_GetError() );
        success = false;
    }
    //Create window
    gWindow = SDL_CreateWindow( CurrentVersion, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error:%s\n", SDL_GetError() );
        success = false;
    }
    //Set icon
    SDL_SetWindowIcon(gWindow,IMG_Load( "resources/icon1.png" ));
    SDL_Cursor *cursor = SDL_CreateColorCursor(IMG_Load( "resources/cursor4.png" ),0,0);
    SDL_SetCursor(cursor);

    //Create window renderer
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }

    //Initialise render colour
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    //Initialise PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialise! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    if ( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialise! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    //Get window surface
    gScreenSurface = SDL_GetWindowSurface( gWindow );

    return success;
}

//Loads media
bool loadMedia()
{
    //Flag
    bool success = true;

    //Load title PNG
    gTexture = loadTexture( "resources/bg0.png" );
    if( gTexture == NULL )
    {
        printf( "Unable to load texture image!" );
        success = false;
    }

    gBG1 = loadTexture( "resources/bg1.png" );
    if( gBG1 == NULL )
    {
        printf( "Unable to load texture image!" );
        success = false;
    }
    gUI1 = loadTexture( "resources/ui/topBG.png" );
    if( gUI1 == NULL )
    {
        printf( "Unable to load texture image!" );
        success = false;
    }
    shadow = loadTexture("resources/ui/shadow.png");
    grass1 = loadTexture("resources/tile/0/grass1.png");
    dirt1 = loadTexture("resources/tile/0/dirt1.png");
    water1 = loadTexture("resources/tile/0/water1.png");
    sand1 = loadTexture("resources/tile/0/sand1.png");

    tree1 = loadTexture("resources/tile/1/tree1.png");
    tree2 = loadTexture("resources/tile/1/tree2.png");
    tree3 = loadTexture("resources/tile/1/tree3.png");
    tree4 = loadTexture("resources/tile/1/tree4.png");

    if( grass1 == NULL or dirt1 == NULL or water1 == NULL or sand1 == NULL or tree1 == NULL or tree2 == NULL or tree3 == NULL or tree4 == NULL)
    {
        printf( "Unable to load a tile image!" );
        success = false;
    }

    storageSolid = loadTexture("resources/tile/2/tier1/storage_solid.png");
    storageLiquid = loadTexture("resources/tile/2/tier1/storage_liquid.png");
    storageGas = loadTexture("resources/tile/2/tier1/storage_gas.png");
    storageRadio = loadTexture("resources/tile/2/tier1/storage_radio.png");
    collectorSolid = loadTexture("resources/tile/2/tier1/collect_solid.png");
    collectorLiquid = loadTexture("resources/tile/2/tier1/collect_liquid.png");
    collectorGas = loadTexture("resources/tile/2/tier1/collect_gas.png");

    pipeStraight = loadTexture("resources/tile/3/tier1/hor_vert.png");

    vesselCard = loadTexture("resources/elementCards/Vessel.png");

    sel = loadTexture("resources/tile/sel.png");
    msgbox2 = loadTexture("resources/ui/msgbox2_3.png");
    hovbox = loadTexture("resources/ui/hovbox1.png");
    vigbox = loadTexture("resources/ui/windowvigentte.png");
    buildingInfoBack = loadTexture("resources/ui/buildingInfo.png");
    //Load music
    gMusic = Mix_LoadMUS( MUS3 );
    if( gMusic == NULL )
    {
        printf( "Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gMusic2 = Mix_LoadMUS( MUS4 );
    if( gMusic2 == NULL )
    {
        printf( "Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gMusic3 = Mix_LoadMUS( MUS2 );
    if( gMusic3 == NULL )
    {
        printf( "Failed to load credits music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gHoverSFX = Mix_LoadWAV( SFX1 );
    if( gHoverSFX == NULL )
    {
        printf( "Failed to load hover sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gSelectSFX = Mix_LoadWAV( SFX2 );
    if( gSelectSFX == NULL )
    {
        printf( "Failed to load select sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

//Clears media and closes SDL
void close()
{
    //Deallocate texture
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Free music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}

//Save array
void save()
{
    std::ofstream arrayData;
    arrayData.open("demo.world");
    for(int i=0; i < worldLayers; i++)
    {
        for(int ii=0; ii < 30; ii++)
        {
            for(int iii=0; iii < 30; iii++)
            {
                arrayData<<world[i][ii][iii][0][0];
            }
            arrayData<<std::endl;
        }
        arrayData<<std::endl;
        arrayData<<std::endl;
    }
    arrayData.close();

}

void setResources()
{
    //Tile indexing
    tile[0][0][0] = grass1;
    tile[0][1][0] = dirt1;
    tile[0][2][0] = water1;
    tile[0][3][0] = sand1;

    //tile[1][0][0] = empty;
    tile[1][1][0] = tree1;
    tile[1][2][0] = tree2;
    tile[1][3][0] = tree3;
    tile[1][4][0] = tree4;

    //tile[2][0][0] = empty;
    tile[2][1][0] = storageSolid;
    tile[2][2][0] = storageLiquid;
    tile[2][3][0] = storageGas;
    tile[2][4][0] = storageRadio;
    tile[2][5][0] = collectorSolid;
    tile[2][6][0] = collectorLiquid;
    tile[2][9][0] = collectorGas;

    tile[3][1][0] = pipeStraight;

    dataName[0] = "H Yield:  ";
    dataName[1] = "He Yield: ";

    //Buildings
    build[1][0][0] = 1;
    build[2][0][0] = 1;
    build[3][0][0] = 1;
    build[4][0][0] = 1;
    build[5][0][0] = 1;
    build[6][0][0] = 1;
    build[9][0][0] = 1;

    build[1][0][1] = 20;
    build[2][0][1] = 45;
    build[3][0][1] = 45;
    build[4][0][1] = 80;
    build[5][0][1] = 30;
    build[6][0][1] = 55;
    build[9][0][1] = 55;

    build[1][2][0] = 1;
    build[2][2][0] = 1;
    build[3][2][0] = 1;
    build[4][2][0] = 3;
    build[5][2][0] = 2;
    build[6][2][0] = 2;
    build[9][2][0] = 2;
}

//Play sound
void quitGame()
{
    Mix_PlayChannel( -1, gSelectSFX, 0 );
    printf("\nShutting Down!");
    //SDL_Delay(500);
}


int main( int argc, char* args[] )
{
    //Start SDL and create window
    if( !init() )
    {
        printf( "Failed to initialise!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop - changes depending on what state we are in
            bool quit = false;
            printf("who cares...\n\nThe game is now working. Nothing is broken. Everything is as it should be.\n");
            std::cout << "Current Resolution: "<<SCREEN_WIDTH<<"x"<<SCREEN_HEIGHT<<". Scale: "<<RS<<std::endl;
            //Event handler
            SDL_Event e;
            int gameState = STATE_TITLE; //Starting state
            while( !quit )
            {
                //State switch
                switch( gameState )
                {
                case STATE_TITLE:
                    while( gameState == STATE_TITLE and !quit )
                    {
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitGame();
                                quit = true;
                            }

                            //Check mouse locations
                            int x, y;
                            SDL_GetMouseState(&x,&y);

                            //User presses first button
                            if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*630,RS*320,(getRenderedWidth(menuItems[0], FONT, 48*RS)),RS*35))
                            {
                                Mix_PlayChannel( -1, gSelectSFX, 0 );
                                gameState = STATE_DMENU;
                                printf("\nChanging state to Demo Menu!");
                            }

                            //User presses last button
                            else if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*(630+(20*3)),RS*(320+(50*3)),(getRenderedWidth(menuItems[3], FONT, 48*RS)),RS*35))
                            {
                                quitGame();
                                quit = true;
                            }

                            //User presses upper button
                            else if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,SCREEN_WIDTH-((getRenderedWidth("Credits",FONT,16*RS)+150)*RS),8*RS,getRenderedWidth("Credits",FONT,16*RS),16*RS))
                            {
                                gameState = STATE_CREDITS;
                                Mix_PlayMusic( gMusic3, 0 );
                            }
                        }
                        SDL_RenderClear( gRenderer );
                        renderTitleScreen();

                        //Render menu items
                        renderMenu(menuItems);

                        //Update screen
                        SDL_RenderPresent( gRenderer );

                        //Play music
                        if( Mix_PlayingMusic() == 0 )
                        {
                            Mix_PlayMusic( gMusic, 0 );
                        }
                    }
                    break;
                case STATE_CREDITS:

                    while( gameState == STATE_CREDITS and !quit )
                    {
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitGame();
                                quit = true;
                            }
                        }
                        SDL_RenderClear( gRenderer );

                        //Render
                        my--;
                        renderCredits(my);

                        //Update screen
                        SDL_RenderPresent( gRenderer );

                        //Play music
                        if( Mix_PlayingMusic() == 0 )
                        {
                            Mix_PlayMusic( gMusic3, 0 );
                        }
                    }
                    break;
                case STATE_DMENU:
                    while( gameState == STATE_DMENU and !quit )
                    {
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitGame();
                                quit = true;
                            }
                            //Check mouse locations
                            int x, y;
                            SDL_GetMouseState(&x,&y);

                            //User presses first button
                            if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*630,RS*320,(getRenderedWidth(menuItems[0], FONT, 48*RS)),RS*35))
                            {
                                Mix_PlayChannel( -1, gSelectSFX, 0 );
                                gameState = STATE_DEMENU;
                                printf("\nChanging state to Demo Erratic Menu!");
                            }

                            //User presses last button
                            else if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*(630+(20*3)),RS*(320+(50*3)),(getRenderedWidth(menuItems[3], FONT, 48*RS)),RS*35))
                            {
                                Mix_PlayChannel( -1, gSelectSFX, 0 );
                                gameState = STATE_TITLE;
                                printf("\nChanging state to Title!");
                            }
                        }
                        SDL_RenderClear( gRenderer );
                        renderTitleScreen();

                        //Render menu items
                        renderMenu(demoMenuItems);

                        SDL_RenderPresent( gRenderer );
                        if( Mix_PlayingMusic() == 0 )
                        {
                            Mix_PlayMusic( gMusic, 0 );
                        }
                    }
                    break;
                case STATE_DEMENU:
                    while( gameState == STATE_DEMENU and !quit )
                    {
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitGame();
                                quit = true;
                            }
                            //Check mouse locations
                            int x, y;
                            SDL_GetMouseState(&x,&y);

                            //User presses first button
                            if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*630,RS*320,(getRenderedWidth(demoErraticMenuItems[0], FONT, 48*RS)),RS*35))
                            {
                                Mix_PlayChannel( -1, gSelectSFX, 0 );
                                gameState = STATE_DEGAME;
                                printf("\nChanging state to Demo Erratic Game!");
                                Mix_PlayMusic( gMusic2, 0 );

                            }

                            //User presses last button
                            else if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*(630+(20*3)),RS*(320+(50*3)),(getRenderedWidth(menuItems[3], FONT, 48*RS)),RS*35))
                            {
                                Mix_PlayChannel( -1, gSelectSFX, 0 );
                                gameState = STATE_DMENU;
                                printf("\nChanging state to Demo Menu!");
                            }
                        }
                        //Demo Erratic Menu
                        SDL_RenderClear( gRenderer );
                        renderTitleScreen();

                        //Render menu items
                        renderMenu(demoErraticMenuItems);

                        SDL_RenderPresent( gRenderer );
                        if( Mix_PlayingMusic() == 0 )
                        {
                            Mix_PlayMusic( gMusic, 0 );
                        }
                    }
                    break;
                case STATE_DEGAME:

                    //Resource resetting
                    int tPhase = 118,tShift = 0;
                    int money = 20;
                    int gen_mat = 580;
                    int selected_building = 1;
                    int building_amount = 9;
                    int H = 10;
                    int He = 27;
                    int C = 380;
                    info[0] = 0;
                    info[1] = 0;
                    bool displayInfo = false;
                    int infoLayer = -1;

                    setResources();

                    worldGenerator demoGenerator;
                    demoGenerator.createWorld(24,12,16);

                    /**LOAD SAVE DATA
                    std::ifstream loadData("demo.world");
                    if(loadData.is_open())
                    {
                        for(int i=0; i < worldLayers; i++)
                        {
                            for(int ii=0; ii < 32; ii++)
                            {
                                for(int iii=0; iii < 32; iii++)
                                {
                                    loadData>>world[i][ii][iii][0][0];
                                }
                            }
                        }
                    }**/


                    //Put the render in the default location
                    int renderTopLeftX = 0, renderTopLeftY = 0;
                    sendToRender(renderTopLeftX,renderTopLeftY);

                    //Create a new class to help do some stuff
                    interfaceHandler demoInterface;

                    //Handle some input events
                    while( gameState == STATE_DEGAME and !quit )
                    {
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            //User requests quit
                            if( e.type == SDL_QUIT )
                            {
                                quitGame();
                                quit = true;
                            }

                            //Keyboard control
                            if( e.type == SDL_KEYDOWN )
                            {
                                int x,y;
                                SDL_GetMouseState(&x,&y);
                                switch( e.key.keysym.sym )
                                {
                                //Camera movement
                                case SDLK_LEFT:
                                    if( renderTopLeftX > 0 )
                                    {
                                        renderTopLeftX--;
                                    }
                                    break;

                                case SDLK_RIGHT:
                                    if( renderTopLeftX < 16 )
                                    {
                                        renderTopLeftX++;
                                    }
                                    break;

                                case SDLK_UP:
                                    if( renderTopLeftY > 0 )
                                    {
                                        renderTopLeftY--;
                                    }
                                    break;

                                case SDLK_DOWN:
                                    if( renderTopLeftY < 22 )
                                    {
                                        renderTopLeftY++;
                                    }
                                    break;

                                //Building, upgrading and destruction
                                case SDLK_b:
                                    if (mouseOn(x,y,100*RS,50*RS,760*RS,440*RS))
                                    {
                                        int gamex = xLocation(55*RS,100*RS)+ renderTopLeftX,
                                            gamey = yLocation(55*RS,50*RS) + renderTopLeftY;
                                        if( world[0][gamex][gamey][0][0] != 2  and world[1][gamex][gamey][0][0] == 0 and !isBuilding(gamex,gamey) and money >= (getBuildingCost(0,2,selected_building)) and gen_mat >= (getBuildingCost(1,2,selected_building)) )
                                        {
                                            world[2][gamex][gamey][0][0] = selected_building;
                                            world[2][gamex][gamey][0][1] = build[selected_building][2][0];
                                            money-=getBuildingCost(0,2,selected_building);
                                            gen_mat-=getBuildingCost(1,2,selected_building);
                                        }
                                    }
                                    break;
                                case SDLK_a:
                                    if( selected_building < building_amount )
                                    {
                                        if( selected_building != 6 )
                                        {
                                            selected_building++;
                                        }
                                        else
                                        {
                                            selected_building=9;
                                        }
                                    }
                                    break;
                                case SDLK_z:
                                    if( selected_building > 1 )
                                    {
                                        if( selected_building != 9 )
                                        {
                                            selected_building--;
                                        }
                                        else
                                        {
                                            selected_building=6;
                                        }

                                    }
                                    break;
                                case SDLK_p:
                                    if (mouseOn(x,y,100*RS,50*RS,760*RS,440*RS))
                                    {
                                        int gamex = xLocation(55*RS,100*RS)+ renderTopLeftX,
                                            gamey = yLocation(55*RS,50*RS) + renderTopLeftY;
                                        if( world[3][gamex][gamey][0][0] == 0 )
                                        {
                                            world[3][gamex][gamey][0][0] = 1;
                                        }
                                    }
                                    break;

                                default:
                                    break;
                                }
                            }

                            if( e.button.button == SDL_BUTTON_RIGHT and e.type == SDL_MOUSEBUTTONDOWN and !justChangedInfoLayer )
                            {
                                justChangedInfoLayer = true;
                                if( xLocation(RS*55,RS*100) != -1 and yLocation(RS*55,RS*50) != -1 )
                                {
                                    if( info[0] == xLocation(RS*55,RS*100)+renderTopLeftX and info[1] == yLocation(RS*55,RS*50)+renderTopLeftY || info[0] == -1 and info[1] == -1 )
                                    {
                                        if( infoLayer==worldLayers-1 )
                                        {
                                            infoLayer=-1;
                                            displayInfo=false;
                                        }
                                        else
                                        {
                                            infoLayer++;
                                            displayInfo=true;
                                        }
                                    }
                                    else
                                    {
                                        info[0] = xLocation(RS*55,RS*100)+renderTopLeftX;
                                        info[1] = yLocation(RS*55,RS*50)+renderTopLeftY;
                                        infoLayer=0;
                                        displayInfo=true;
                                    }
                                }
                                else
                                {
                                    infoLayer=-1;
                                    displayInfo=false;
                                }
                            }
                            else
                            {
                                justChangedInfoLayer = false;
                            }
                        }

                        //Render game and UI backgrounds
                        SDL_RenderClear( gRenderer );
                        renderTexture(gBG1,0,0,RS*10,RS*10);
                        renderTexture(gUI1,0,0,RS*5,RS*5);
                        renderTexture(gUI1,0,RS*490,RS*5,RS*5);


                        //User presses "Save/Quit"
                        int x, y;
                        SDL_GetMouseState(&x,&y);
                        if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*151,RS*503,getRenderedWidth("Save/Quit",FONT,30*RS),RS*20))
                        {
                            save();
                            Mix_PlayChannel( -1, gSelectSFX, 0 );
                            gameState = STATE_DEMENU;
                            printf("\nChanging state to Demo Erratic Menu!");
                            Mix_PlayMusic( gMusic, 0 );
                        }
                        //User presses "Advance"
                        else if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,RS*670,RS*503,getRenderedWidth("Advance",FONT,30*RS),RS*20) and !justPressedAdvance)
                        {
                            if(tShift<99)
                            {
                                tShift++;
                            }
                            else
                            {
                                tShift=0;
                                tPhase++;
                            }
                            for( int i=0; i<30; i++ ) //The y axis loop
                            {
                                for( int ii=0; ii<30; ii++ ) //The x axis loop
                                {
                                    if(world[2][ii][i][0][0] > 0 and !isFunctional(ii,i)) //If there is a building that isn't complete
                                    {
                                        world[2][ii][i][0][1]--; //Do some stuff to it
                                    }
                                }
                            }
                            justPressedAdvance = true;
                        }
                        if( e.type == SDL_MOUSEBUTTONUP )
                        {
                            justPressedAdvance = false;
                        }

                        //Minimap movement - code could be improved
                        int minimapFlag = 0; //Number of times the map hasn't been moved to the edge during this movement
                        SDL_GetMouseState(&x,&y); //Get where the mouse is
                        if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and mouseOn(x,y,870*RS,49*RS,100*RS,90*RS)) //If the mouse is left clicked over the minimap
                        {
                            if( mouseOn(x,y,870*RS,42*RS,50*RS,76*RS) ) //If the mouse is in the top left portion where the rectangle can be moved without clipping the edge of the map
                            {
                                renderTopLeftX=(x-870*RS)/(3*RS); //Set the render position with the mouse position
                                renderTopLeftY=(y-50*RS)/(3*RS); //Set the render position with the mouse position
                            }
                            else //If the mouse is in the bottom right portion
                            {
                                if( mouseOn(x,y,870*RS,42*RS,100*RS,76*RS) ) //If the mouse is in the top portion
                                {
                                    renderTopLeftX=16; //Set the render position to the maximum
                                    renderTopLeftY=(y-50*RS)/(3*RS); //Set the render position with the mouse position
                                }
                                else //If the mouse isn't
                                {
                                    minimapFlag++; //Increment failed edge movements
                                }
                                if( mouseOn(x,y,870*RS,42*RS,50*RS,100*RS) ) //If the mouse is in the left portion
                                {
                                    renderTopLeftY=22; //Set the render position to the maximum
                                    renderTopLeftX=(x-870*RS)/(3*RS); //Set the render position with the mouse position
                                }
                                else //If the mouse isn't
                                {
                                    minimapFlag++; //Increment failed edge movements
                                }
                                if( minimapFlag > 1 ) //If we have two failed edge movements we are in the corner
                                {
                                    renderTopLeftX=16; //Set the render position to the maximum
                                    renderTopLeftY=22; //Set the render position to the maximum
                                }

                            }
                        }

                        //Resource management
                        std::string money_string = concadenatorBinary("Money:\n   ",money);
                        std::string genmat_string = concadenatorTrinary("Matter:\n   ",gen_mat,"t");
                        std::string time = concadenatorTime(tPhase,tShift);
                        std::string Hs = concadenatorBinary("H: ",H);
                        std::string Hes = concadenatorBinary("He:",He);
                        std::string Cs = concadenatorBinary("C: ",C);
                        demoInterface.renderInterface(time,money_string,genmat_string, Hs, Hes, Cs);

                        //Hover
                        demoInterface.interfaceHover();

                        //Technology
                        renderTexture(vesselCard,0,RS*50,RS*0.625,RS*0.625);

                        //World render update
                        sendToRender(renderTopLeftX,renderTopLeftY);

                        //World render
                        SDL_SetTextureAlphaMod(tile[3][1][0],150);
                        for(int i=0; i<8; i++) //The y axis loop
                        {
                            for(int ii=0; ii<14; ii++) //The x axis loop
                            {
                                renderTexture(tile[0][render[0][ii][i]][0],RS*(100+55*ii),RS*(50+55*i),RS*5,RS*5); //Render the base layer
                                for(int iii=worldLayers-1; iii>0; iii--) //Iterate down all other layers
                                {
                                    if( render[iii][ii][i] > 0 ) //If the array contains a block at the current position
                                    {
                                        if( iii != 3 ) //If it isn't the pipe layer
                                        {
                                            renderTexture(tile[iii][render[iii][ii][i]][0],RS*(100+55*ii),RS*(50+55*i),RS*5,RS*5); //Render it
                                            if( iii == 2) //If it is the building layer
                                            {
                                                if( world[2][ii+renderTopLeftX][i+renderTopLeftY][0][0] > 0 and world[2][ii+renderTopLeftX][i+renderTopLeftY][0][1] > 0 ) //If the current building is incomplete
                                                {
                                                    renderFont(
                                                               (static_cast<std::ostringstream*>( &(std::ostringstream() << world[2][ii+renderTopLeftX][i+renderTopLeftY][0][1]) )->str()),
                                                                FONT,colorR,64*RS,(RS*100+RS*55*ii)+18*RS,(RS*50+RS*55*i)+8*RS,0); //Render the number
                                                }
                                            }
                                        }
                                        else //If it is the pipe layer
                                        {
                                            if( world[3][ii+renderTopLeftX][i+1+renderTopLeftY][0][0] == 1 or world[3][ii+renderTopLeftX][i-1+renderTopLeftY][0][0] == 1) //If there is another pipe below or above the current pipe
                                            {
                                                if ( world[3][ii+1+renderTopLeftX][i+renderTopLeftY][0][0] == 1 or world[3][ii-1+renderTopLeftX][i+renderTopLeftY][0][0] == 1 ) //If there is also another pipe to the left or right of the pipe
                                                {
                                                    renderTexture(tile[3][render[3][ii][i]][0],RS*(100+55*ii),RS*(50+55*i),RS*5,RS*5); //Render the horizontal pipe
                                                }
                                                rotateTexture(tile[3][render[3][ii][i]][0],RS*(100+55*ii),RS*(50+55*i),RS*5,RS*5,90); //Render the vertical pipe
                                            }
                                            else //If there are no pipes above or below this pipe
                                            {
                                                renderTexture(tile[3][render[3][ii][i]][0],RS*(100+55*ii),RS*(50+55*i),RS*5,RS*5); //Render the horizontal pipe
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        //Map render
                        for( int i=0; i<30; i++ ) //The y axis loop
                        {
                            for( int ii=0; ii<30; ii++ ) //The x axis loop
                            {
                                if( i < 29 ) //If the current row is anything but the last
                                {
                                    for( int iii=0; iii<worldLayers; iii++ ) //The z axis loop
                                    {
                                        if( iii != 3) //If this isn't the pipe layer
                                        {
                                            renderTexture(tile[iii][world[iii][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.3)); //Render the object/tile
                                        }
                                        else //If this is the pipe layer
                                        {
                                            if( world[3][ii][i][0][0] > 0 ) //If there is a pipe on the current position
                                            {
                                                if( world[3][ii][i+1][0][0] == 1 or world[3][ii][i-1][0][0] == 1) //If there is a pipe below or above the current position
                                                {
                                                    if( world[3][ii+1][i][0][0] == 1 or world[3][ii-1][i][0][0] == 1 ) //And there is a pipe next to the current position
                                                    {
                                                        renderTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.3)); //Render the horizontal pipe
                                                    }
                                                    rotateTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.3),90); //Render the vertical pipe
                                                }
                                                else //If there is not a pipe above or below
                                                {
                                                    renderTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.3)); //Render the horizontal pipe
                                                }
                                            }
                                        }
                                    }
                                }
                                else //If this is the last row
                                {
                                    for( int iii=0; iii<worldLayers; iii++ ) //The z axis loop
                                    {
                                        if( iii != 3) //If this isn't the pipe layer
                                        {
                                            renderTexture(tile[iii][world[iii][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.2)); //Render the object/tile (Note: the tile is scaled diferently)
                                        }
                                        else
                                        {
                                            if( world[3][ii][i][0][0] > 0 ) //If there is a pipe on the current position
                                            {
                                                if( world[3][ii][i+1][0][0] == 1 or world[3][ii][i-1][0][0] == 1) //If there is a pipe below or above the current position
                                                {
                                                    if( world[3][ii+1][i][0][0] == 1 or world[3][ii-1][i][0][0] == 1 ) //And there is a pipe next to the current position
                                                    {
                                                        renderTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.2)); //Render the horizontal pipe (Note: the tile is scaled diferently)
                                                    }
                                                    rotateTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.2),90); //Render the vertical pipe (Note: the tile is scaled diferently)
                                                }
                                                else //If there is not a pipe above or below
                                                {
                                                    renderTexture(tile[3][world[3][ii][i][0][0]][0],(RS*(870+(ii*3))),(RS*(50+(i*3))),(RS*0.3),(RS*0.2)); //Render the horizontal pipe (Note: the tile is scaled diferently)
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        //Construction prompts
                        SDL_GetMouseState(&x,&y); //Get the mouse position
                        renderTexture(msgbox2,0,210*RS,5*RS,5*RS); //Render the message box
                        if( mouseOn( x,y,100*RS,50*RS,760*RS,440*RS ) and !displayBuildingInfo
                           ) //If the mouse is on the world
                        {
                            //Other commands/info
                            renderFont("Next [A]\nPrev [Z]",FONT,color,16*RS,8*RS,431*RS,75*RS); //Render Next/Previous commands
                            renderFont(getBuildingName(2,selected_building),FONT,color,16*RS,8*RS,312*RS,90*RS); //Render building name
                            renderFont(concadenatorBinary("Money: ",getBuildingCost(0,2,selected_building)),FONT,colorS,16*RS,8*RS,340*RS,90*RS); //Render building cost
                            renderFont(concadenatorTrinary("Matter: ",getBuildingCost(1,2,selected_building),"t"),FONT,colorS,16*RS,8*RS,354*RS,90*RS); //Render building materials

                            //Ghost
                            SDL_SetTextureAlphaMod(tile[2][selected_building][0],100); //Make current building transparent
                            renderTexture(tile[2][selected_building][0],(RS*100+RS*55*(xLocation(55*RS,100*RS))),(RS*50+RS*55*(yLocation(55*RS,50*RS))),RS*5,RS*5); //Render ghost of building
                            SDL_SetTextureAlphaMod(tile[2][selected_building][0],255); //Make building opaque again

                            //Message Box
                            renderFont("Build[B]",FONT,colorD,16*RS,8*RS,403*RS,90*RS); //Render build command in orange
                            renderFont("Pipe [P]",FONT,colorS,16*RS,8*RS,417*RS,90*RS); //Render pipe command
                            if( world[1][xLocation(55*RS,100*RS)+ renderTopLeftX][yLocation(55*RS,50*RS) + renderTopLeftY][0][0] == 0 //If the current square has no decoration
                                    and world[0][xLocation(55*RS,100*RS)+ renderTopLeftX][yLocation(55*RS,50*RS) + renderTopLeftY][0][0] != 2 //Is not ocean
                                    and world[2][xLocation(55*RS,100*RS)+ renderTopLeftX][yLocation(55*RS,50*RS) + renderTopLeftY][0][0] == 0)//And does not have a building
                            {
                                if( money >= (getBuildingCost(0,2,selected_building)) and gen_mat >= (getBuildingCost(1,2,selected_building)) ) //If there is enough resources
                                {
                                    renderFont("Build[B]",FONT,colorS,16*RS,8*RS,403*RS,90*RS); //Render build command in blue
                                }
                                else //If there are not enough resources
                                {
                                    renderFont("Out of resources",FONT,colorR,16*RS,8*RS,270*RS,90*RS); //Render resource message
                                    if( money < (getBuildingCost(0,2,selected_building))) //If there isn't enough money
                                    {
                                        renderFont(concadenatorBinary("Money: ",getBuildingCost(0,2,selected_building)),FONT,colorR,16*RS,8*RS,340*RS,90*RS); //Render money requirement in red
                                    }
                                    if( gen_mat < (getBuildingCost(1,2,selected_building))) //If there isn't enough matter
                                    {
                                        renderFont(concadenatorTrinary("Matter: ",getBuildingCost(1,2,selected_building),"t"),FONT,colorR,16*RS,8*RS,354*RS,90*RS); //Render material requirement in red
                                    }
                                }
                            }
                            else //If the site is invalid
                            {
                                renderFont("Invalid Site",FONT,colorR,16*RS,8*RS,270*RS,90*RS); //Render site message
                                renderFont(concadenatorBinary("Money: ",getBuildingCost(0,2,selected_building)),FONT,color,16*RS,8*RS,340*RS,90*RS); //I can't remember why these are here
                                renderFont(concadenatorTrinary("Matter: ",getBuildingCost(1,2,selected_building),"t"),FONT,color,16*RS,8*RS,354*RS,90*RS); //I can't remember why these are here
                            }
                        }

                        //View area rectangle
                        SDL_Rect viewRect = {RS*(870+renderTopLeftX*3),RS*(50+renderTopLeftY*3),RS*42,RS*24};
                        SDL_RenderDrawRect(gRenderer,&viewRect);

                        //Show/hide cursor
                        if(xLocation(RS*55,RS*100) != -1 and yLocation(RS*55,RS*50) != -1 and !displayBuildingInfo)
                        {
                            SDL_ShowCursor(0);
                            renderTexture(sel,(RS*100+RS*55*(xLocation(55*RS,100*RS))),(RS*50+RS*55*(yLocation(55*RS,50*RS))),RS*5,RS*5);
                        }
                        else
                        {
                            SDL_ShowCursor(1);
                        }

                        //Building Info
                        SDL_GetMouseState(&x,&y); //Get where the mouse is
                        if( e.button.button == SDL_BUTTON_LEFT and
                            e.type == SDL_MOUSEBUTTONDOWN and
                            xLocation(RS*55,RS*100) != -1 and yLocation(RS*55,RS*50) != -1 and
                            !displayBuildingInfo and !justPressedBuildingInfo and
                            world[2][xLocation(RS*55,RS*100)+renderTopLeftX][yLocation(RS*55,RS*50)+renderTopLeftY][0][0] > 0)
                        {
                            displayBuildingInfo = true;
                            printf("YEP");
                            justPressedBuildingInfo = true;
                            binfo[0]=xLocation(RS*55,RS*100)+renderTopLeftX;
                            binfo[1]=yLocation(RS*55,RS*50)+renderTopLeftY;
                        }
                        if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONDOWN and !mouseOn(x,y,200,110,560,320) and displayBuildingInfo and !justPressedBuildingInfo)
                        {
                            displayBuildingInfo = false;
                            printf("NOPE");
                            justPressedBuildingInfo = true;
                        }
                        if( e.button.button == SDL_BUTTON_LEFT and e.type == SDL_MOUSEBUTTONUP )
                        {
                            justPressedBuildingInfo = false;
                        }

                        //Info
                        SDL_SetTextureAlphaMod(hovbox,150);
                        if(displayInfo and infoLayer >-1 and info[0]>=renderTopLeftX and info[1]>=renderTopLeftY)
                        {
                            renderTexture(hovbox,(RS*100+RS*55*(info[0]+1-renderTopLeftX)),(RS*50+RS*55*(info[1]+1-renderTopLeftY)),RS*5,RS*5);
                            renderFont(concadenatorBinary("Layer: ",infoLayer),FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*66+RS*55*(info[1]+1-renderTopLeftY)),0);
                            if( infoLayer == 0 )
                            {
                                renderFont(getBuildingName(0,world[0][info[0]][info[1]][0][0]),FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*82+RS*55*(info[1]+1-renderTopLeftY)),0);
                                for(int i = 0; i < 2; i++)
                                {
                                    renderFont(concadenatorBinary(dataName[i],data[i][info[0]][info[1]]),FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*82+((i+1)*16*RS)+RS*55*(info[1]+1-renderTopLeftY)),0);
                                }
                            }
                            else if( infoLayer == 1 )
                            {
                                if( world[1][info[0]][info[1]][0][0] > 0 )
                                {
                                    renderFont("Occupied",FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*82+RS*55*(info[1]+1-renderTopLeftY)),0);
                                }
                                else
                                {
                                    renderFont("No Object",FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*82+RS*55*(info[1]+1-renderTopLeftY)),0);
                                }
                            }
                            else if( infoLayer == 2 )
                            {
                                renderFont(getBuildingName(2,world[2][info[0]][info[1]][0][0]),FONT,colorB,16*RS,(RS*116+RS*55*(info[0]+1-renderTopLeftX)),(RS*82+RS*55*(info[1]+1-renderTopLeftY)),90*RS);
                            }
                        }

                        //test
                        renderTexture(vigbox,100*RS,50*RS,10*RS,10*RS);

                        //Building info
                        if(displayBuildingInfo)
                        {
                            renderScreenCentre(buildingInfoBack,8*RS);
                            renderFontCentered(getBuildingName(2,world[2][binfo[0]][binfo[1]][0][0]),FONT,color,48*RS,SCREEN_WIDTH/2,SCREEN_HEIGHT/2 - 130*RS);
                            if(isFunctional(binfo[0],binfo[1]))
                            {
                                //Functional data
                            }
                            else
                            {
                                //Building not functional


                            }
                        }

                        //Render Everything
                        SDL_RenderPresent( gRenderer );

                        //Play music
                        if( Mix_PlayingMusic() == 0 )
                        {
                            Mix_PlayMusic( gMusic2, 0 );
                        }
                    }
                }
            }
        }
    }

    //Close SDL
    close();

    return 0;
}
