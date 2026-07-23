#include <stdio.h>
#include <stdlib.h>
#include "../globals.h"

uint32_t *spriteSheet = NULL;


int* scaleSprite(int *sprite, int spriteHeight, int spriteWidth, float scaleFactor){
    int newSpriteHeight = (int)((float)spriteHeight * scaleFactor);
    int newSpriteWidth = (int)((float)spriteWidth * scaleFactor);

    int *newSprite = malloc(sizeof(int) * newSpriteHeight * newSpriteWidth);

    for (int y = 0; y < newSpriteHeight; y++){
        for (int x = 0; x < newSpriteWidth; x++){
            int srcX = (int)((float)x / scaleFactor);
            int srcY = (int)((float)y / scaleFactor);
            int srcIndex = srcY * spriteWidth + srcX;
            newSprite[y * newSpriteWidth + x] = sprite[srcIndex];
        }
    }

    return newSprite;
}

