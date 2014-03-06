//Version
const char* CurrentVersion = "Phase 118 - Lithium [Alpha] 0.3.2.4";

//Parameters
float RS = 1.5;
const int SCREEN_WIDTH = ceil(RS*960);
const int SCREEN_HEIGHT = (SCREEN_WIDTH/16)*9;

//Paths
const char* FONT = "resources/Courier-Pixel.ttf";
const char* MUS1 = "resources/mod.wav";
const char* MUS2 = "resources/happy.wav";
const char* MUS3 = "resources/sad.wav";
const char* SFX1 = "resources/hov.wav";
const char* SFX2 = "resources/sel.wav";
const char* MUS4 = "resources/echo.wav";

//Menus
std::string menuItems[] = {"Demo","Impact","Haven","Quit"};
std::string demoMenuItems[] = {"Erratic","Typical","Advanced","Back"};
std::string demoErraticMenuItems[] = {"New Game","Continue","Options","Back"};

//Credits
std::string credits[] = {
    "Phase 118", //B
    "Developed by", //H
    "Harrison Scott",
    "Graphics by", //H
    "Harrison Scott",
    "Daniel Kimber",
    "Consultance", //H
    "is help"
    "come back in a year for full game",
    "Copyright is not valid until 2054", //H
    "DONT SUE" //B
};

//Colours
SDL_Color color = {255,255,255};
SDL_Color colorS = {80,150,230};
SDL_Color colorD = {230,150,80};
SDL_Color colorB = {0,0,0};
SDL_Color colorR = {230,23,23};

//SDL Pointers
SDL_Window* gWindow = NULL;             //Game window
SDL_Surface* gScreenSurface = NULL;     //Game window surface
SDL_Renderer* gRenderer = NULL;         //Window renderer
SDL_Texture* gTexture = NULL;           //Title screen

SDL_Texture* gBG1 = NULL;               //Game background
SDL_Texture* gUI1 = NULL;               //UI background (upper)

Mix_Music *gMusic = NULL;               //Menu music
Mix_Music *gMusic2 = NULL;
Mix_Music *gMusic3 = NULL;
Mix_Chunk *gHoverSFX = NULL;            //Hover sfx
Mix_Chunk *gSelectSFX = NULL;           //Select sfx

SDL_Texture* vesselCard = NULL;

//Tiles
SDL_Texture* grass1 = NULL;
SDL_Texture* dirt1 = NULL;
SDL_Texture* water1 = NULL;
SDL_Texture* sand1 = NULL;

//Decorations
SDL_Texture* tree1 = NULL;
SDL_Texture* tree2 = NULL;
SDL_Texture* tree3 = NULL;
SDL_Texture* tree4 = NULL;

//Buildings
SDL_Texture* storageSolid = NULL;
SDL_Texture* storageLiquid = NULL;
SDL_Texture* storageGas = NULL;
SDL_Texture* storageRadio = NULL;
SDL_Texture* collectorSolid = NULL;
SDL_Texture* collectorLiquid = NULL;
SDL_Texture* collectorGas = NULL;

//Pipes
SDL_Texture* pipeStraight = NULL;

//UI
SDL_Texture* sel = NULL;
SDL_Texture* msgbox2 = NULL;
SDL_Texture* shadow = NULL;
SDL_Texture* hovbox = NULL;
SDL_Texture* vigbox = NULL;
SDL_Texture* buildingInfoBack = NULL;

//Tile array
SDL_Texture* tile[worldLayers][16][1];

//World array
int render [worldLayers][14][8];
int world [worldLayers][32][32][3][2];

//Data array
int data [16][32][32];
int build [16][3][2];

//States
enum gameStates
{
    STATE_TITLE,            //Title Screen
    STATE_CREDITS,

    STATE_DMENU,            //Demo Menu
    STATE_IMENU,            //Impact Menu
    STATE_HMENU,            //Haven Menu

    STATE_DEMENU,           //Demo>Erratic Menu
    STATE_DEGAME            //Demo>Erratic>Game
};

//Checking things
bool wasJustOnButton[] = {false,false,false,false};
bool inGame = true;
bool justChangedInfoLayer = false;
bool justPressedAdvance = false;
bool displayBuildingInfo = false;
bool justPressedBuildingInfo = false;
int info [2];
int binfo [2];
std::string dataName [2];

int my = SCREEN_HEIGHT + 50*RS;
