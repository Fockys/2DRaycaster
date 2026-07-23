#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include "SDL3/SDL.h"

//graphics
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern int* gFrameBuffer;
extern SDL_Window* gSDLWindow;
extern SDL_Renderer* gSDLRenderer;
extern SDL_Texture* gSDLTexture;
extern int gDone;

//player
extern double playerPosX;
extern double playerPosY;

//look dirrection is a 2d vector for easier calculation
extern double playerLookDirX;
extern double playerLookDirY;

#define playerFOV 90


extern char* dataLocation;
extern uint32_t *spriteSheet;

#endif