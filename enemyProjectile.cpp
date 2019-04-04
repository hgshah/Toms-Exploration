#include "enemyProjectile.h"


#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define EN_JOY_STEPS_PER_PIXEL_SHOOT 16

Adafruit_ILI9341 tft4 = Adafruit_ILI9341(TFT_CS, TFT_DC);


EnemyProjectile::EnemyProjectile(){

    projSize = 3;



};



void EnemyProjectile::setDirection(int X, int Y, int tomX, int tomY){

    xPos = X;
    yPos = Y;

    xTom = tomX;
    yTom = tomY;

    xDir = (xTom - xPos) / EN_JOY_STEPS_PER_PIXEL_SHOOT;
    yDir = (yTom - yPos) / EN_JOY_STEPS_PER_PIXEL_SHOOT;
    if(xDir > 0){

        xPos = xPos + 16;
    }
    else if(xDir < 0){

        xPos = xPos - 16;
    }

    if(yDir > 0){

        yPos = yPos + 16;
    }
    else if(yDir < 0){

        yPos = yPos - 16;
    }




    



};   


bool EnemyProjectile::shoot(int ctX, int ctY){

    tft4.setRotation(-1);

    if (xDir != 0 || yDir != 0) {

        tft4.fillCircle(xPos, yPos, projSize, GREY);

        xPos = xPos + xDir;
        yPos = yPos + yDir;

       


        tft4.fillCircle(xPos, yPos, projSize, SLIME);
    }
    int d = 100;
    int x = fabs(xPos - ctX);
    int y = fabs(yPos - ctY);
    if(x <= 9 || y <= 9){

        d = sqrt(x*x + y*y);
    }


    if(xPos > TFT_WIDTH - projSize || xPos < projSize || yPos > TFT_HEIGHT - projSize || yPos < projSize || d <= 12 ) {

        tft4.fillCircle(xPos, yPos, projSize, GREY);
        xDir = 0;
        yDir = 0;

        xPos = 0;
        yPos = 0;  

        xTom = 0;
        yTom = 0;

    }

    if(d <= 12){

        return true;
    }
    else{

        return false;
    }













};