#include "SDL3/SDL.h"

#include "../globals.h"
#include <stdlib.h>



int initialiseGraphics(){

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)){
        return -1;
    }
    gFrameBuffer = malloc(WINDOW_HEIGHT*WINDOW_WIDTH*sizeof(*gFrameBuffer));
    gSDLWindow = SDL_CreateWindow("SDL3 window", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    gSDLRenderer = SDL_CreateRenderer(gSDLWindow, NULL);
    gSDLTexture = SDL_CreateTexture(gSDLRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!gFrameBuffer || !gSDLWindow || !gSDLRenderer || !gSDLTexture){
        return -1;
    }
    gDone = 0;

}

void cleanupGraphics(){

    SDL_DestroyTexture(gSDLTexture);
    SDL_DestroyRenderer(gSDLRenderer);
    SDL_DestroyWindow(gSDLWindow);
    SDL_Quit();
    free(gFrameBuffer);

}