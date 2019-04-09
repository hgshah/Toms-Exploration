# Toms-exploration

Its a game where tom passes separate levels and fights with enemy.  Its build on C++ and Arduino using dynamic memory, classes and mathematical algorithms

Harsh G Shah
Student ID: 1561306
Sean Rutherford
Student ID: 1516423

Wiring instructions:

Board Pin <---> Arduino Pin
===========================
General + Touchscreen:

GND             GND
Vin             5V
3Vo             NOT CONNECTED
CLK             52
MISO            50
MOSI            51
CS              10
D/C             9
RST             NOT CONNECTED
Lite            NOT CONNECTED
Y+              A2 (analog pin)
X+              4  (digital pin)
Y-              5  (digital pin)
X-              A3 (analog pin)
IM0 - IM3       NOT CONNECTED (they expect a 3.3v signal, DON'T CONNECT!)
CCS             6
CD              NOT CONNECTED

Movement Joystick:
GND             GND
+5v             5V
VRx             A1
VRy             A0
SW              2

Shooting Joystick:
GND             GND
+5v             5V
VRx             A4
VRy             A5
SW              3


Running instruction:

To run, wire the arduino, and plug into computer, then enter directory 'Project' and type command 'make upload'. Now press the movement joystick to begin, use the movement joystick to move the player and the shooting joytick to aim and fire projectiles, hit the enemy 10 times before he can run your health down to zero.

Mile stone week-1
We discussed the idea of making the best use of C++ and arduino, 
hence we decided to make a game which uses the concepts of edmonton map and its applications, hash table, dynamic memory and arrays.
First idea was to make layers of game and create a base.
Secondly we researched about the memory allocations which the arduino can withstand.
Hence we avoided the concept of STL libraries as it wasnt supported by arduino.
After Making the base and layers we moved on to making the shooter  using the tft.fillrect and tft.draw
We later moved on to movement of the shooter which was done using the joystick

Mile stone  week-2
After the shooter was moving, we implemented the shooting part
As shooting was implemented we were not able to move the shooter while shooting , hence was make that happen 
So until now the shooter can move while shooting
Next part is the projectile:
here we used arrays and few mathematical concepts such as pythgores thoerem to implement this idea
we later created enemies which on the next layer after creating a door on the first layer

Mile stone week-3
We now implementaed the projectile shooting of the enemies and make the enemies move
we now made the shooting to disapper once the ball hits the shooter or the enemy or wall
We implemented the starting screen to enter the game and health was created for shooter
we made the health to decrease by 25% each time the ball hits the shooter

   
