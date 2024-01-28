#ifndef IDN_H_
#define IDN_H_
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Surface *gBackground;
extern SDL_Surface *gBackground1;
extern SDL_Surface *gBird1;
extern SDL_Surface *gBird2;
extern SDL_Surface *gBird3;
extern SDL_Surface *gSling;
extern SDL_Surface *gSling2;
extern SDL_Surface *gpig;
extern SDL_Surface *gboard1;
extern SDL_Surface *gboard2;
extern SDL_Surface *gButtonLevelsOpen;
extern SDL_Surface *gButtonLevelsClose;
extern SDL_Surface *gButton_Next;
extern SDL_Surface *gButton_Levels;
extern SDL_Surface *gButton_Retry;

bool init();
bool loadMedia();
void closeGame();

#endif