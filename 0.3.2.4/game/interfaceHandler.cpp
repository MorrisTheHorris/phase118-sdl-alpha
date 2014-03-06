#include "interfaceHandler.h"
#include "../include.h"
#include "../renderSimple.h"
#include "../mouseAction.h"

interfaceHandler::interfaceHandler()
{
    //ctor
    if( inGame )
    {
        printf("\n\nYep you are in the game. Have fun. This is it.");
        inGame = false;
    }
}

interfaceHandler::~interfaceHandler()
{
    //dtor
}

void interfaceHandler::renderInterface(std::string time, std::string money, std::string genmat, std::string H, std::string He, std::string C)
{
    renderFont("Technology",FONT,color,RS*30,RS*115,RS*14,0);
    renderFont("Economics",FONT,color,RS*30,RS*305,RS*14,0);
    renderFont("Environment",FONT,color,RS*30,RS*477,RS*14,0);
    renderFont(time,FONT,color,RS*30,RS*694,RS*14,0);
    renderFont("Save/Quit",FONT,color,RS*30,RS*151,RS*503,0);
    renderFont("Information",FONT,color,RS*30,RS*388,RS*503,0);
    renderFont("Next Shift",FONT,color,RS*30,RS*670,RS*503,0);
    renderFont(money,FONT,color,16*RS,RS*872,RS*200,100*RS);
    renderFont(genmat,FONT,color,16*RS,RS*872,RS*230,100*RS);
    renderFont(H,FONT,color,16*RS,RS*872,RS*260,100*RS);
    renderFont(He,FONT,color,16*RS,RS*872,RS*275,100*RS);
    renderFont(C,FONT,color,16*RS,RS*872,RS*290,100*RS);
}

void interfaceHandler::interfaceHover()
{
    int x, y;
    SDL_GetMouseState(&x,&y);
    if( mouseOn(x,y,RS*151,RS*503,getRenderedWidth("Save/Quit",FONT,30*RS),RS*20) )
    {
        renderFont("Save/Quit",FONT,colorS,RS*30,RS*151,RS*503,0);
    }
    if( mouseOn(x,y,RS*670,RS*503,getRenderedWidth("Next Shift",FONT,30*RS),RS*20) )
    {
        renderFont("Next Shift",FONT,colorS,RS*30,RS*670,RS*503,0);
    }

}
