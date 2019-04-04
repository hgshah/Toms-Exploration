#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <TouchScreen.h>
#include <stdlib.h>
//#include <vector>
#include "playerTom.h"
#include "playerProjectile.h"
#include "enemies.h"
#include "enemyProjectile.h"

// TFT display and SD card will share the hardware SPI interface.
// For the Adafruit shield, these are the default.
// The display uses hardware SPI, plus #9 & #10
// Mega2560 Wiring: connect TFT_CLK to 52, TFT_MISO to 50, and TFT_MOSI to 51.
#define TFT_DC 9
#define TFT_CS 10
#define SD_CS 6

// joystick pins
#define JOY_VERT_ANALOG A1
#define JOY_HORIZ_ANALOG A0
#define JOY_SEL 2

// shooting joystick pins
#define JOY_VERT_ANALOG_SHOOT A4
#define JOY_HORZ_ANALOG_SHOOT A5
#define JOY_SEL_SHOOT 3

// width/height of the display when rotated horizontally
#define TFT_WIDTH 320
#define TFT_HEIGHT 240

// layout of display for this assignment,
//#define RATING_SIZE 48
#define DISP_WIDTH TFT_WIDTH
#define DISP_HEIGHT TFT_HEIGHT

// constants for the joystick
#define JOY_DEADZONE 64
#define JOY_CENTRE 512
#define JOY_STEPS_PER_PIXEL 240
#define JOY_STEPS_PER_PIXEL_SHOOT 100

// touch screen pins, obtained from the documentaion
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM  5  // can be a digital pin
#define XP  4  // can be a digital pin

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

// Cursor size. For best results, use an odd number.
#define CURSOR_SIZE 9

// number of restaurants to display
#define REST_DISP_NUM 30


#define GREY 0xC618
#define BLOOD 0xB145
#define STONE 0xA514

#define PROJECTILES_NUM 100

#define EN_PROJ_NUM 25

// Use hardware SPI (on Mega2560, #52, #51, and #50) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// a multimeter reading says there are 300 ohms of resistance across the plate,
// so initialize with this to get more accurate readings
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);





// the currently selected restaurant, if we are in mode 1
//int selectedRest;

// which mode are we in?
int mode;

int CurrentStage;

int I;

int J;

int TF;

int TI;

int ETF;

int ETI;

int T;

int SCORE;

// the current map view and the previous one from last cursor movement

Tom tom(DISP_WIDTH/2, DISP_HEIGHT/2);

Projectile projectiles[PROJECTILES_NUM];

//Enemy Enemy1(20,20);
Enemy Enemy2(100,100);
//Enemy Enemy3(250,130);
//Enemy Enemy4(300,20);




//EnemyProjectile enemy1projectiles[EN_PROJ_NUM];
EnemyProjectile enemy2projectiles[EN_PROJ_NUM];
//EnemyProjectile enemy3projectiles[EN_PROJ_NUM];
//EnemyProjectile enemy4projectiles[EN_PROJ_NUM];




// For sorting and displaying the restaurants, will hold the restaurant RestDist
// information for the most recent click in sorted order.
//RestDist restaurants[NUM_RESTAURANTS];

//Sd2Card card;

//lcd_image_t edmontonBig = { "yeg-big.lcd", MAPWIDTH, MAPHEIGHT };

// The cache of 8 restaurants for the getRestaurant function.
//RestCache cache;

// Forward declaration of functions to begin the modes. Setup uses one, so
// it seems natural to forward declare both (not really that important).
void beginMode0();
void beginMode1();

void setup() {
	init();

	Serial.begin(9600);

	// do not actually need to change the pinmode of the digital TouchScreen
	// pins, the function to get a touchscreen reading will set and change them

	pinMode(JOY_SEL, INPUT_PULLUP);

	tft.begin();

	tft.setRotation(-1);
	tft.setTextWrap(false);

  // initial cursor position is the centre of the screen
  //curView.cursorX = DISP_WIDTH/2;
  //curView.cursorY = DISP_HEIGHT/2;
  //replace
  	//tft.fillScreen(ILI9341_BLUE);

	tft.fillScreen(ILI9341_BLACK);
	tft.drawChar(50,50,'T',BLOOD,2,3);
	tft.drawChar(60,50,'O',BLOOD,2,3);
	tft.drawChar(70,50,'M',BLOOD,2,3);
	//tft.drawChar(90,50,'S',BLOOD,2,3);
	//tft.drawChar(30,70,'A',BLOOD,2,3);
	//tft.drawChar(40,70,'D',BLOOD,2,3);
	//tft.drawChar(50,70,'V',BLOOD,2,3);
	//tft.drawChar(60,70,'E',BLOOD,2,3);
	//tft.drawChar(70,70,'N',BLOOD,2,3);
	//tft.drawChar(80,70,'T',BLOOD,2,3);
	//tft.drawChar(90,70,'U',BLOOD,2,3);
	//tft.drawChar(100,70,'R',BLOOD,2,3);
	//tft.drawChar(110,70,'E',BLOOD,2,3);


	tft.drawChar(50,120,'S',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(60,120,'T',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(70,120,'A',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(80,120,'R',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(90,120,'T',BLOOD,ILI9341_WHITE,3);

  // initial map position is the middle of Edmonton
  //curView.mapX = ((MAPWIDTH / DISP_WIDTH)/2) * DISP_WIDTH;
  //curView.mapY = ((MAPHEIGHT / DISP_HEIGHT)/2) * DISP_HEIGHT;

	// Ensures the first getRestaurant() will load the block as all blocks
	// will start at REST_START_BLOCK, which is 4000000.
	//cache.cachedBlock = 0;

  //beginMode0();
}

void drawStage1(){

    tft.fillScreen(GREY);
    // tft.fillRect(1,180,30,60,ILI9341_WHITE);
    // tft.fillRect(5,222,20,13,ILI9341_RED);
    tft.fillRect(150,0,32,3,ILI9341_BLUE);
    tft.fillRect(30, 215, 100, 20, ILI9341_RED);




}
 
void drawStage2(){



		tft.fillScreen(GREY);
		tft.fillRect(30, 215, 100, 20, ILI9341_RED);
		//tft.fillRect(TFT_WIDTH/2, DISP_HEIGHT/2, 50, 20, STONE);
		//Enemy Enemy1(20,20);
		//Enemy Enemy2(20,200);
		//Enemy Enemy3(300,200);
		//Enemy Enemy4(300,20);

		//EnemyProjectile enemy1projectiles[EN_PROJ_NUM];
		//EnemyProjectile enemy2projectiles[EN_PROJ_NUM];
		//EnemyProjectile enemy3projectiles[EN_PROJ_NUM];
		//EnemyProjectile enemy4projectiles[EN_PROJ_NUM];

		//Enemy1.draw();
		Enemy2.draw();
		//Enemy3.draw();
		//Enemy4.draw();

}







void moveCursor() {
	
	if (CurrentStage == 1){
	
		tft.fillCircle(tom.pxPos, tom.pyPos, CURSOR_SIZE, GREY);
	}
	else{
	
		tft.fillCircle(tom.pxPos, tom.pyPos, CURSOR_SIZE, GREY);
	}

	tft.fillCircle(tom.xPos, tom.yPos , CURSOR_SIZE, ILI9341_RED);
}


void beginMode0() {
	
 	drawStage1();


	// just the initial draw of the player
	moveCursor();

  	mode = 1;
}

void beginMode1(){

	tft.fillScreen(ILI9341_BLACK);
	tft.drawChar(50,50,'T',BLOOD,2,3);
	tft.drawChar(60,50,'O',BLOOD,2,3);
	tft.drawChar(70,50,'M',BLOOD,2,3);
	//tft.drawChar(90,50,'S',BLOOD,2,3);
	//tft.drawChar(30,70,'A',BLOOD,2,3);
	//tft.drawChar(40,70,'D',BLOOD,2,3);
	//tft.drawChar(50,70,'V',BLOOD,2,3);
	//tft.drawChar(60,70,'E',BLOOD,2,3);
	//tft.drawChar(70,70,'N',BLOOD,2,3);
	//tft.drawChar(80,70,'T',BLOOD,2,3);
	//tft.drawChar(90,70,'U',BLOOD,2,3);
	//tft.drawChar(100,70,'R',BLOOD,2,3);
	//tft.drawChar(110,70,'E',BLOOD,2,3);


	tft.drawChar(50,120,'S',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(60,120,'T',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(70,120,'A',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(80,120,'R',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(90,120,'T',BLOOD,ILI9341_WHITE,3);

	mode = 0;


}


// Checks if the edge was nudged and scrolls the map if it was.
void checkRedrawMap() {
  // A flag to indicate if we scrolled.
	bool scroll = false;

	

	if (tom.yPos == CURSOR_SIZE && tom.xPos < 182 && tom.xPos > 150) {
		
		scroll = true;
	}

	// If we nudged the edge, recalculate and draw the new rectangular portion of Edmonton to display.
	if (scroll && CurrentStage==0) {
		tom.yPos = DISP_HEIGHT - 20;
		// Make sure we didn't scroll outside of the map.
		//curView.mapX = constrain(curView.mapX, 0, MAPWIDTH - DISP_WIDTH + RATING_SIZE);
		//curView.mapY = constrain(curView.mapY, 0, MAPHEIGHT - DISP_HEIGHT);
		CurrentStage = 1;
		drawStage2();

		//lcd_image_draw(&edmontonBig, &tft, curView.mapX, curView.mapY, 0, 0, DISP_WIDTH, DISP_HEIGHT);
	}
}

// Process joystick and touchscreen input when in mode 0.
void scrollingMap() {

 	int v = analogRead(JOY_VERT_ANALOG);
  	int h = analogRead(JOY_HORIZ_ANALOG);
  	int invSelect = digitalRead(JOY_SEL);

  	int q = analogRead(JOY_VERT_ANALOG_SHOOT);
  	int p = analogRead(JOY_HORZ_ANALOG_SHOOT);
 	int melee = digitalRead(JOY_SEL_SHOOT);


	// A flag to indicate if the player moved or not.
	bool cursorMove = false;

	bool playerShoot = false;

  // If there was vertical movement, then move the player
  	if (abs(v - JOY_CENTRE) > JOY_DEADZONE) {
    // First move the cursor.
    
    	int delta = (v - JOY_CENTRE) / JOY_STEPS_PER_PIXEL;
		// Clamp it so it doesn't go outside of the screen.
    	tom.yPos = constrain(tom.yPos + delta, CURSOR_SIZE, DISP_HEIGHT-CURSOR_SIZE - 1);
		// And now see if it actually moved.
		cursorMove |= (tom.yPos != tom.pyPos);
 	}

	// If there was horizontal movement, then move the player.
  	if (abs(h - JOY_CENTRE) > JOY_DEADZONE) {
   
   
    	int delta = -(h - JOY_CENTRE) / JOY_STEPS_PER_PIXEL;
    
    	tom.xPos = constrain(tom.xPos+ delta, CURSOR_SIZE, TFT_WIDTH-CURSOR_SIZE - 1);
		cursorMove |= (tom.xPos != tom.pxPos);
  	}

	// If the player actually moved.
	if (cursorMove) {
		
		// Check if the door was nudged, and move to map2 if so.
		checkRedrawMap();	
		
		

		// Now draw the cursor's new position.
		moveCursor();
		//delay(20);
	}

	tom.pxPos = tom.xPos;
	tom.pyPos = tom.yPos;

	int yProjDir = 0;
	int xProjDir = 0;

	if (abs(q - JOY_CENTRE) > JOY_DEADZONE) {

		playerShoot = true;
    	yProjDir = (q - JOY_CENTRE) / JOY_STEPS_PER_PIXEL_SHOOT;
    	//Serial.println(yProjDir);
    }

    if (abs(p - JOY_CENTRE) > JOY_DEADZONE) {
    
   		playerShoot = true;
    	xProjDir = -(p - JOY_CENTRE) / JOY_STEPS_PER_PIXEL_SHOOT;
	}

	if(true) {

		while (projectiles[I].xDir != 0 || projectiles[I].yDir != 0){

			I++;

			if(I == PROJECTILES_NUM - 1){
				I = 0;
			}

		}
		
		TF = millis();

		int delayProj = TF - TI;
		//Serial.println(delayProj);

		if (delayProj > 500){

			projectiles[I].setDirection(xProjDir, yProjDir, tom.xPos, tom.yPos);
			TI = millis();
		}


		//projectiles[I].setDirection(xProjDir, yProjDir, tom.xPos, tom.yPos);

		for (int i = 0; i < PROJECTILES_NUM; i++){
		
			bool enhit = projectiles[i].shoot(Enemy2.xPos, Enemy2.yPos);

			if(enhit){

				//int k = digitalRead(13);

				//int p = digitalRead(12);

				tft.fillCircle(Enemy2.xPos,Enemy2.yPos,8, GREY);

				if(Enemy2.xPos < 280){
					Enemy2.xPos += 10;
				}
				else{
					Enemy2.xPos = 30;
				}
				if(Enemy2.yPos < 210){
					Enemy2.yPos += 10;
				}
				else{
					Enemy2.yPos = 30;
				}
				

				Enemy2.draw();

				SCORE += 1;

				tft.drawChar(300, 20, SCORE + 48, ILI9341_RED, ILI9341_BLACK, 4);

				if(SCORE >= 10){
					beginMode1();

				}






			}
		}

		//TI = millis();

		


	}

	if(CurrentStage == 1){

		while (enemy2projectiles[J].xDir != 0 || enemy2projectiles[J].yDir != 0){

			J++;

			if(J == EN_PROJ_NUM - 1){
				J = 0;
			}

		}

		ETF = millis();
		int endelayProj = ETF - ETI;

		Serial.println(endelayProj);

		if (endelayProj > 1000){

			//enemy1projectiles[J].setDirection(Enemy1.xPos, Enemy1.yPos, tom.xPos, tom.yPos);
			enemy2projectiles[J].setDirection(Enemy2.xPos, Enemy2.yPos, tom.xPos, tom.yPos);
			//enemy3projectiles[J].setDirection(Enemy3.xPos, Enemy3.yPos, tom.xPos, tom.yPos);
			//enemy4projectiles[J].setDirection(Enemy4.xPos, Enemy4.yPos, tom.xPos, tom.yPos);

			ETI = millis();
	    }



	    
		for (int j = 0; j < EN_PROJ_NUM; j++){
			
			//enemy1projectiles[j].shoot(tom.xPos, tom.yPos);
	
			
			bool hit = enemy2projectiles[j].shoot(tom.xPos, tom.yPos);

			if(hit){

				tom.health -= 25;
				tft.fillRect(30 + tom.health, 215, 100 - tom.health, 20, GREY);
				if(tom.health <= 0){

					beginMode1();

				


			

				}
			}
			

		}	


		

			



		


		






		















	}
		
		
		


		
		








}














	//preView = curView;

	// Did we click the joystick?
  /*if(invSelect == LOW){
		beginMode1();
    mode = 1;
    Serial.println(mode);
    Serial.println("MODE changed.");

		// Just to make sure the restaurant is not selected by accident
		// because the button was pressed too long.
		while (digitalRead(JOY_SEL) == LOW) { delay(10); }
  }*/

	// check if the restaurant button was pressed. If so, draw the restaurants.

	// Check for touchscreen press and draws dots for each restaurant
	//TSPoint touch = ts.getPoint();

	//if (touch.z >= MINPRESSURE && touch.z <= MAXPRESSURE) {

		//tft.fillScreen(ILI9341_BLUE);
		/*restaurant r;
		
		// just iterate through all restaurants on the card
		for (int i = 0; i < NUM_RESTAURANTS; ++i) {
			getRestaurant(&r, i, &card, &cache);
			int16_t rest_x_tft = lon_to_x(r.lon)-curView.mapX, rest_y_tft = lat_to_y(r.lat)-curView.mapY;

			// only draw if entire radius-3 circle will be in the map display
			if (rest_x_tft >= 3 && rest_x_tft < DISP_WIDTH-3 &&
			    rest_y_tft >= 3 && rest_y_tft < DISP_HEIGHT-3) {
						tft.fillCircle(rest_x_tft, rest_y_tft, 3, ILI9341_BLUE);
					}
		}*/
	



void scrollingMenu(){

	//tft.fillScreen(ILI9341_BLACK);
	tft.drawChar(50,50,'T',BLOOD,2,3);
	tft.drawChar(70,50,'O',BLOOD,2,3);
	tft.drawChar(90,50,'M',BLOOD,2,3);
	//tft.drawChar(110,50,'S',BLOOD,2,3);
	//tft.drawChar(30,75,'A',BLOOD,2,3);
	//tft.drawChar(50,75,'D',BLOOD,2,3);
	//tft.drawChar(70,75,'V',BLOOD,2,3);
	//tft.drawChar(90,75,'E',BLOOD,2,3);
	//tft.drawChar(110,75,'N',BLOOD,2,3);
	//tft.drawChar(130,75,'T',BLOOD,2,3);
	//tft.drawChar(150,75,'U',BLOOD,2,3);
	//tft.drawChar(170,75,'R',BLOOD,2,3);
	//tft.drawChar(190,75,'E',BLOOD,2,3);


	tft.drawChar(50,120,'S',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(70,120,'T',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(90,120,'A',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(110,120,'R',BLOOD,ILI9341_WHITE,3);
	tft.drawChar(130,120,'T',BLOOD,ILI9341_WHITE,3);
	
	if (digitalRead(JOY_SEL) == LOW) {

		beginMode0();

		// Ensures a long click of the joystick will not register twice.
		while (digitalRead(JOY_SEL) == LOW) { delay(10); }
	}
}






int main() {
	setup();

	// All the implementation work is done now, just have a loop that processes
	// joystick movement!
	while (true) {
		if (mode == 0) {
			scrollingMenu();
		}
		else {
			scrollingMap();
		}
	}

	Serial.end();
	return 0;
}
