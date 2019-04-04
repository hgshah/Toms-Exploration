#include "enemies.h"
#define PINK 0xD0DD

#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 6

Adafruit_ILI9341 tft3 = Adafruit_ILI9341(TFT_CS, TFT_DC);

   

Enemy::Enemy(int X,int Y){

     xPos = X;
     yPos = Y;

}
 void Enemy::draw(){
    tft3.setRotation(-1);
    tft3.fillCircle(xPos,yPos,8,PINK);



}