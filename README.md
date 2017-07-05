
About:
This is a simple program which uses cannon to destroy the falling blocks, and the coloured boxes for catching their 
respective coloured blocks.
Aim of the game is to shoot as many black blocks and collect the coloured block in their respective colour boxes thereby scoring as high as possible.

RULES:
-> Shooting the Black block with Cannon will score +5 , shooting anything else wont fetch any points but
   will still destroy the blocks.
-> To score points with Green and Red blocks, you need to catch them in their respective coloured boxes +5 ,else +2.
-> If any block lands on the base, there will be a DEDUCTION of 5 points.
-> As time progresses , speed of each blocks will start increasing.
-> You will loose if any black block lands on the base.

Features:
All the features described in the assignment criteria were successfully implemented.
Apart from that the following things are implemented too-

 (SPECIAL FEATURE) 
 	There is a purple coloured crystal in the game which is a POWERUP.
 	Collecting the crytal will destroy all blocks presently on the screen and a +10 of score.
 	But if u choose to hit that power up with a laser , it will attain you 20 points, but will increase the speed of the upcoming blocks.

 	Also except the mirror at the center of the screen the left and right walls are also reflecting (to make the game interesting) and top and bottom walls are absorbing(as per required feature).

 (SOUND FEATURE)
 	Sounds when the laser shoots, or when the block blasts. Game ending music and power up sound has also been implemented.

 (SCORE BOARD AND TEXT)
 	Continuous running scoreboard has been implemented too. It Even shows text at pause and at GAME OVER!!!		



How to run:
-> The makefile compiles the code. (Type 'make' on the terminal)
-> Now type './Game' (on terminal) to run the executable.

Controls:
-> You can use the right and left arrow keys to move and up and down arrow keys to rotate the cannon.
-> Use 'r' , 'g' to get control of the respective coloured boxes and then use right and left arrow keys for movement.
-> Press 'c' to get back the control of the cannon.
-> USE OF MOUSE CONTROL HAS ALSO BEEN SUCCESSFULLY IMPLEMENTED!!!
-> Use spacebar to fire laser.(NOTE: YOU CAN FIRE ONLY 1 LASER PER SECOND)
-> For zoom in press 'z' and zoom out press 'x'. This can also be done by mouse scroll.
-> 'm' to increse block speed  and 'n' to decrease the speed. 
-> 'p' to pause the game and q or ESC' to quit the game.

type g++ -Wall -o Game Game.cpp -lglut -lGL -lGLU on terminal to compile.
