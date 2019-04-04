#include "playerProjectile.h"


#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define Sapphire 0x1C3F
#define GREY 0xC618
#define BOOMRED 0xD800

Adafruit_ILI9341 tft2 = Adafruit_ILI9341(TFT_CS, TFT_DC);
    
Projectile::Projectile(){
    xDir = 0;
    yDir = 0;


};

bool Projectile::shoot(int ctX, int ctY){
    tft2.setRotation(-1);
    if (xDir != 0 || yDir != 0) {
    
        //xPos = xPos + xDir;
       // yPos = yPos + yDir;

        tft2.fillCircle(xPos, yPos, projSize, GREY);

        xPos = xPos + xDir;
        yPos = yPos + yDir;

        tft2.fillCircle(xPos, yPos, projSize, Sapphire);

    }
    int d = 100;
    int x = fabs(xPos - ctX);
    int y = fabs(yPos - ctY);
    if(x <= 8 || y <= 8){

        d = sqrt(x*x + y*y);
    }

    if(xPos > TFT_WIDTH - projSize || xPos < projSize || yPos > TFT_HEIGHT - projSize || yPos < projSize || d <= 12) {

        tft2.fillCircle(xPos, yPos, projSize, GREY);
        xDir = 0;
        yDir = 0;

        xPos = 0;
        yPos = 0;  
    }

    if(d <= 12){
        return true;
    }
    else{

        return false;
    }





   
};


void Projectile::setDirection(int X, int Y, int OGX, int OGY){

    xDir = X;
    yDir = Y;
    

    xPos = OGX;
    yPos = OGY;

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
        



        
      
    
    //tft2.fillRect(xPos, yPos, projSize, projSize, GREY);




