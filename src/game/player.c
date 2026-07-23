#include "../globals.h"
#include <math.h>
#include "../map.h"

double playerPosX;
double playerPosY;
double playerLookDirX;
double playerLookDirY;

void initPlayer(){
    playerPosX = 5;
    playerPosY = 5;
    playerLookDirX = 1;
    playerLookDirY = 0;
}

int isValidPos(double x, double y){
    if(globalMap[(int)x][(int)y]==0){
        return true;
    }
    return false;
}

void movePlayer(double X, double Y){
    if(isValidPos(X,Y)){
        playerPosX = X;
        playerPosY = Y;
    }else{
        
    }

}


void playerTurn(double angle){
    double tempX = (playerLookDirX*cos(angle)-(playerLookDirY*sin(angle)));
    double tempY = (playerLookDirX*sin(angle))+ (playerLookDirY*cos(angle));
    playerLookDirX = tempX;
    playerLookDirY = tempY;
}

static const double turnSpeed = M_PI;       // radians per second
static const double moveSpeed = 3.0;        // units per second

void playerTurnRight(double deltaTime){
    playerTurn(turnSpeed * deltaTime);
}

void playerTurnLeft(double deltaTime){
    playerTurn(-turnSpeed * deltaTime);
}

void playerForward(double deltaTime){
    double step = moveSpeed * deltaTime;
    double X = playerPosX + (playerLookDirX * step);
    double Y = playerPosY + (playerLookDirY * step);
    movePlayer(X,Y);
}

void playerBackward(double deltaTime){
    double step = moveSpeed * deltaTime;
    double X = playerPosX - (playerLookDirX * step);
    double Y = playerPosY - (playerLookDirY * step);
    movePlayer(X,Y);
}

void playerStrafeLeft(double deltaTime){
    double step = moveSpeed * deltaTime;
    double X = playerPosX + (playerLookDirY * step);
    double Y = playerPosY - (playerLookDirX * step);
    movePlayer(X,Y);
}

void playerStrafeRight(double deltaTime){
    double step = moveSpeed * deltaTime;
    double X = playerPosX - (playerLookDirY * step);
    double Y = playerPosY + (playerLookDirX * step);
    movePlayer(X,Y);
}