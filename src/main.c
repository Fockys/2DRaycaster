#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "SDL3/SDL_main.h"
#include "graphics/graphicsMain.h"
#include "graphics/graphicsHelper.h"
#include "graphics/raycasts.h"
#include "game/player.h"
#include "game/sprites.h"

#include <math.h>
#include "map.h"

// Define global variables
const int globalMap[mapWidth][mapHeight] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,2,2,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

int testSprite[5][5] = {
    {0xffffffff,0xff00ffff,0xffffffff,0xff00ffff,0xffffffff},
    {0xffffffff,0xff00ffff,0xffffffff,0xff00ffff,0xffffffff},
    {0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff},
    {0xff00ffff,0xffffffff,0xffffffff,0xffffffff,0xff00ffff},
    {0xff00ffff,0xff00ffff,0xff00ffff,0xff00ffff,0xff00ffff}
};

int *scaledSprite;

int* gFrameBuffer = NULL;
SDL_Window* gSDLWindow = NULL;
SDL_Renderer* gSDLRenderer = NULL;
SDL_Texture* gSDLTexture = NULL;
int gDone = 0;

void init(){
    initPlayer();
    initialiseGraphics();

    printf("Init finished");
}


bool update(double deltaTime){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT){
            return false;
        }
        if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE){
            return false;
        }
    }

    const bool* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_LEFT]){
        playerTurnLeft(deltaTime);
    }
    if (keys[SDL_SCANCODE_RIGHT]){
        playerTurnRight(deltaTime);
    }
    if (keys[SDL_SCANCODE_W]){
        playerForward(deltaTime);
    }
    if (keys[SDL_SCANCODE_S]){
        playerBackward(deltaTime);
    }
    if (keys[SDL_SCANCODE_A]){
        playerStrafeLeft(deltaTime);
    }
    if (keys[SDL_SCANCODE_D]){
        playerStrafeRight(deltaTime);
    }

    char* pix;
    int pitch;
    
    SDL_LockTexture(gSDLTexture, NULL, (void**)&pix, &pitch);
    for (int i = 0, sp = 0, dp = 0; i < WINDOW_HEIGHT; i++, dp += WINDOW_WIDTH, sp += pitch)
        memcpy(pix + sp, gFrameBuffer + dp, WINDOW_WIDTH * 4);

    SDL_UnlockTexture(gSDLTexture);  
    SDL_RenderTexture(gSDLRenderer, gSDLTexture, NULL, NULL);
    SDL_RenderPresent(gSDLRenderer);
    SDL_Delay(1);
    return true;
}

void render(Uint64 aTicks){
    fillScreen(0x000000ff);
    drawRaycasts();
}

void printPlayerPos(){
    printf("%f %f \n",playerPosX,playerPosY);
}
void printPlayerLookDirDegrees(){
    double angle = atan(playerLookDirY/playerLookDirX);
    printf("angle: %f\n",angle * (180/M_PI));
}


void loop(double deltaTime){
    if (!update(deltaTime)){
        gDone = 1;
    }
    else{
        render(SDL_GetTicks());
        printPlayerPos();
        printPlayerLookDirDegrees();
    }

}




int main(int argc, char** argv){
    init();

    Uint64 lastTicks = SDL_GetTicks();
    while(!gDone){
        Uint64 currentTicks = SDL_GetTicks();
        double deltaTime = (currentTicks - lastTicks) / 1000.0;
        lastTicks = currentTicks;
        loop(deltaTime);
    }

    cleanupGraphics();
    return 0;
}