#include "../globals.h"


void fillScreen(int colour){
    for(int pixel = 0; pixel < WINDOW_HEIGHT*WINDOW_WIDTH; pixel++){
        gFrameBuffer[pixel] = colour;
    }
}

void drawPixel(int x, int y, int colour){
    int bufferPixel = WINDOW_WIDTH*y + x;
    if(bufferPixel < WINDOW_WIDTH * WINDOW_HEIGHT){
        gFrameBuffer[WINDOW_WIDTH*y+x] = colour;    
    } 
}

//smaller value start
void drawVertical(int x, int start, int end, int colour){
    if(x<0 || x> WINDOW_WIDTH) return;
    if(start<0 || start> WINDOW_HEIGHT){
        start = 0;
    };
    if(end<0 || end> WINDOW_HEIGHT){
        end = WINDOW_HEIGHT;
    };
    for(int y = start; y<end; y++){
        gFrameBuffer[WINDOW_WIDTH*y+x] = colour;
    }
}

//draw sprite to screen, sprite is a pointer to the start of 2d array, sprite must be cast to (int *)
void drawSprite(int *sprite, int spriteHeight, int spriteWidth, int spriteX, int spriteY){

    if(spriteX+spriteWidth > WINDOW_WIDTH) return;
    if(spriteY+spriteHeight > WINDOW_HEIGHT) return;

    for(int x = 0; x<spriteWidth; x++){
        for(int y = 0; y<spriteHeight; y++){
            gFrameBuffer[(y+spriteY)*WINDOW_WIDTH + (x+spriteX)] = sprite[y*spriteWidth + x];
        }
    }
}

