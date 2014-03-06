#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>

#include <cstdlib>
#include <time.h>

/** A METHOD TO THE MADNESS
 *  AKA I ABUSE ARRAYS
 *
 *  We have 4 arrays currently:
 *  world[][][][][] which contains the data for each x-y-layer entity
 *  The first dimension is layer - this saves using multiple arrays i.e. world0[][][][], world1[][][][]
 *  The next two are x and y, or it might be y and x sometimes (TODO - fix that)
 *  The next dimension works as follows:
 *      [0] is the index and status part of this dimension
 *          When dealing with a fourth dimension of 0, the fifth dimension of [0] is the index and [1] is the status in time units
 *      [1] is the capacity part of this dimension
 *          When dealing with a fourth dimension of 1, the fifth dimension of [r] is the max store of r and the fifth dimension of [r*1000] is the r contents
 *
 *  render[][][] deals with the visible portion of the screen
 *  The dimensions are the same as world yet only the first 3
 *
 *  build[][][] contains building data
 *  The first dimension is the building index
 *  The second dimension works as follows:
 *      [0] is the cost part of the dimension
 *          When dealing with a second dimension of 0, the third dimension of [r] is the r cost to build
 *      [1] is the attribute part of the dimension
 *          *//*not done*//**
 *      [2] is the time part of the dimension
 *          *//*not done*//**
 *
 *   tile[][][] contains all tile images
 *   The first dimension is the layer of tiles
 *   The second dimension is the tile index
 *   The third dimension is the level of tile mostly for buildings
 *
 *   I DO THIS BECAUSE I AM CRAZY BUT IT ALSO MAKES THE MATH EASIER
 */


//Version
extern const char* CurrentVersion;

//Parameters
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern float RS;
const int worldLayers = 4;

//Paths
extern const char* FONT;
extern const char* MUS1;
extern const char* MUS2;
extern const char* MUS3;
extern const char* SFX1;
extern const char* SFX2;

//Menus
extern std::string menuItems[];
extern std::string demoMenuItems[];
extern std::string demoErraticMenuItems[];
extern std::string credits[];

//Colours
extern SDL_Color color;
extern SDL_Color colorS;
extern SDL_Color colorD;
extern SDL_Color colorB;
extern SDL_Color colorR;

//SDL Pointers
extern SDL_Window* gWindow;             //Game window
extern SDL_Surface* gScreenSurfac;     //Game window surface
extern SDL_Renderer* gRenderer;         //Window renderer
extern SDL_Texture* gTexture;           //Current texture
extern SDL_Texture* gBG1;               //Game background

extern Mix_Music *gMusic;               //Menu music
extern Mix_Music *gMusic2;
extern Mix_Music *gMusic3;
extern Mix_Chunk *gHoverSFX;            //Hover sfx
extern Mix_Chunk *gSelectSFX;           //Select sfx

extern SDL_Texture* vesselCard;
extern SDL_Texture* gUI1;
extern SDL_Texture* shadow;
extern SDL_Texture* tile[worldLayers][16][1];
extern SDL_Texture* sel;
extern SDL_Texture* msgbox2;
extern SDL_Texture* hovbox;
extern SDL_Texture* vigbox;
extern SDL_Texture* buildingInfoBack;

//World arrays
extern int render [worldLayers][14][8];
extern int world [worldLayers][32][32][3][2];
extern int data [16][32][32];
extern int build [16][3][2];

//Tiles
extern SDL_Texture* grass1;
extern SDL_Texture* dirt1;
extern SDL_Texture* water1;
extern SDL_Texture* sand1;

//Decorations
extern SDL_Texture* tree1;
extern SDL_Texture* tree2;
extern SDL_Texture* tree3;
extern SDL_Texture* tree4;

//Buildings
extern SDL_Texture* storageSolid;
extern SDL_Texture* storageLiquid;
extern SDL_Texture* storageGas;
extern SDL_Texture* storageRadio;
extern SDL_Texture* collectorSolid;
extern SDL_Texture* collectorLiquid;
extern SDL_Texture* collectorGas;

//Pipes
extern SDL_Texture* pipeStraight;

//Integer Resources
extern int money;
extern int gen_mat;
extern int selected_building;
extern int building_amount;
extern int H;
extern int He;
extern int C;

//Booleans
extern bool wasJustOnButton[];
extern bool inGame;

extern bool displayInfo;
extern int infoLayer;
extern int info [2];
extern int binfo [2];
extern std::string dataName [2];
extern bool displayBuildingInfo;
