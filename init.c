#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include "init.h"
#include <assert.h>



SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gBackground = NULL;
SDL_Surface *gBackground1 = NULL;
SDL_Surface *gBird1 = NULL;
SDL_Surface *gBird2 = NULL;
SDL_Surface *gBird3 = NULL;
SDL_Surface *gSling = NULL; 
SDL_Surface *gSling2 = NULL; 
SDL_Surface *gpig= NULL; 
SDL_Surface* gboard1 = NULL;
SDL_Surface* gboard2 = NULL;
SDL_Surface *gButtonLevelsOpen= NULL;
SDL_Surface *gButtonLevelsClose= NULL;

SDL_Surface *gButton_Next= NULL;
SDL_Surface *gButton_Levels= NULL;
SDL_Surface *gButton_Retry= NULL;


bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL failed to initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() < 0)
    {
        printf("TTFfailed to initialize!TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1400, 600, SDL_WINDOW_SHOWN);
    //SDL_WINDOW_SHOWN
    if (gWindow == NULL)
    {
        printf("Failed to create window! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // gScreenSurface = SDL_GetWindowSurface(gWindow);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf(" failed to initialize SDL_image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

bool loadMedia()
{
    gBackground = IMG_Load("./sky.png");
    if (gBackground == NULL)
    {
        printf("Failed to load background image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gBackground1 = IMG_Load("./darksky.png");
    if (gBackground1 == NULL)
    {
        printf("Failed to load 2 background images SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gSling = IMG_Load("./sling.png");
    if (gSling == NULL)
    {
        printf("Failed to load sling image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gBird1 = IMG_Load("./bird.png");
    if (gBird1 == NULL)
    {
        printf("Failed to load image of bird 1! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gBird2 = IMG_Load("./bird2.png");
    if (gBird2 == NULL)
    {
        printf("Failed to load image of bird 2!SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gBird3 = IMG_Load("./bird3.png");
    if (gBird3 == NULL)
    {
        printf(" Failed to load bird image 3! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gSling2 = IMG_Load("./sling2.png"); 
    if (gSling2 == NULL)
    {
        printf("Failed to load sling2 image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gpig = IMG_Load("./pig.png");
    if (gpig == NULL)
    {
        printf("Failed to load pig image!SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gboard1 = IMG_Load("./board1.png");
    if (gboard1 == NULL)
    {
        printf("Failed to load board1 image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gboard2 = IMG_Load("./board2.png");
    if (gboard2 == NULL)
    {
        printf("Failed to load board2 image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gButtonLevelsOpen = IMG_Load("./level_open.png");
    if (gButtonLevelsOpen == NULL)
    {
        printf("Failed to load level_open image SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gButtonLevelsClose = IMG_Load("./level_close.png");
    if (gButtonLevelsClose == NULL)
    {
        printf("Failed to load image plevel_close ! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
     gButton_Next = IMG_Load("./Next.png");
    if (gButton_Next == NULL)
    {
        printf("Failed to load image Next! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gButton_Levels = IMG_Load("./Levels.png");
    if (gButton_Levels == NULL)
    {
        printf("We were unable to load the Levels image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    gButton_Retry = IMG_Load("./Retry.png");
    if (gButton_Retry == NULL)
    {
        printf("Failed to load Retry image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

void closeGame()
{
    SDL_FreeSurface(gBackground);
    gBackground = NULL;

    SDL_FreeSurface(gBird1);
    gBird1 = NULL;

    SDL_FreeSurface(gBird2);
    gBird2 = NULL;

    SDL_FreeSurface(gBird3);
    gBird3 = NULL;

    SDL_FreeSurface(gSling);
    gSling = NULL;

    SDL_FreeSurface(gSling2);
    gSling2 = NULL;

    SDL_FreeSurface(gpig);
    gpig = NULL;

    SDL_FreeSurface(gboard1);
    gboard1 = NULL;

    SDL_FreeSurface(gboard2);
    gboard1 = NULL;
    
    SDL_FreeSurface(gButtonLevelsOpen);
    gButtonLevelsOpen = NULL;

    SDL_FreeSurface(gButtonLevelsClose);
    gButtonLevelsClose = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_FreeSurface(gButton_Levels);
    gButton_Levels = NULL;

    SDL_FreeSurface(gButton_Next);
    gButton_Next = NULL;

    SDL_FreeSurface(gButton_Retry);
    gButton_Retry = NULL;

    IMG_Quit();

    SDL_Quit();

    TTF_Quit();

}