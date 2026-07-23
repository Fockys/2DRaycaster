#include "../globals.h"
#include <math.h>
#include "../map.h"
#include "../graphics/graphicsHelper.h"
#include <stdio.h>


void drawOneRaycast(int screenX, double rayDrawLenInterval) {
    //results in a value between -1 to 1 to show the offset of ray from the center of screen
    double cameraX = 2.0 * screenX / (double)WINDOW_WIDTH - 1.0;

    //the direction of the plane, perpendicular to look direction
    double planeX = -playerLookDirY;
    double planeY =  playerLookDirX;

    double rayDirX = playerLookDirX + planeX * cameraX;
    double rayDirY = playerLookDirY + planeY * cameraX;

    //calcualte distance from plane to wall
    double distance = 0;
    while (globalMap[(int)(playerPosX + rayDirX * distance)][(int)(playerPosY + rayDirY * distance)] == 0) {
        distance += rayDrawLenInterval;
    }

    //record stopping point and colour
    double stoppedX = playerPosX + rayDirX * distance;
    double stoppedY = playerPosY + rayDirY * distance;
    int colour = globalMap[(int)stoppedX][(int)stoppedY];

    //colour map
    int actualColour;
    if (colour == 1) {
        actualColour = 0xff00ffff;
    } else if (colour == 2) {
        actualColour = 0x00ffffff;
    } else {
        actualColour = 0xffff00ff;
    }

    //dot product between rayDir and playerLookDir
    double perpDist = (rayDirX * playerLookDirX + rayDirY * playerLookDirY) * distance;
    if (perpDist < 0.0001) perpDist = 0.0001; //prevent division by 0

    int drawLineHeight = (int)(500.0 / perpDist);
    int middleScreen   = WINDOW_HEIGHT / 2;
    int halfDist       = drawLineHeight / 2;

    drawVertical(screenX, middleScreen - halfDist, middleScreen + halfDist, actualColour);
}



void drawRaycasts(){
    double rayDrawLenInterval = 0.01;
    for(int x = 0; x<WINDOW_WIDTH; x++){
        drawOneRaycast(x,rayDrawLenInterval);
    }

}