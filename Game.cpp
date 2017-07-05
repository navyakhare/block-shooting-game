
 
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <cstdio>
#include <vector>
#include <unistd.h>
using namespace std;
struct block
{

	float sp_x;
	float sp_y;
	char sp_col;
	int state;
};
struct laser
{
	float x;
	float y;float thet;
	int state;
	int hit_state;
	float nx,ny;
};


#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void play();
void GetOGLPos(int x,int y);
void handlemouse_drag(int x,int y);
void drawpower();
void drawScene();
void createlaser();
void generate(int val);
void drawsquare();
void drawsquare1();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

int score=0;float mouseposx,mouseposy,mouseposz;int click;
int hit_flag=1000;float len1=8.0f;int exit_flag=0;int exit_time=0;
int power_up=0;
int speed_time=0;float block_speed=0.1f;
float temp,temp1;static bool paused=false;
float start=-20.0f;
float end=22.0f;
float ball_x = 1.0f;int flag=1;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float red_x=-16.0f;float red_y=-21.0;
float green_x=16.0f;float green_y=-21.0;
float box_len = 22.0f;
float tri_x = -18.0f;
float tri_y = 0.0f;
float z_cord = -28.0f;
//float tri_x = 2.0f;
//float tri_y = -19.0f;
float theta = 270; char present='c';
vector <struct block> blocks;  //Details about all the blocks
vector <struct block> ::iterator it;
vector <struct block> ::iterator ix;
struct block fallingblock;
vector <struct laser> lasers;    //Details of all lasers
vector <struct laser> ::iterator il;
struct laser las;

int main(int argc, char **argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 10 / 12;
	int windowHeight = h * 10 / 12;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("Game");  // Setup the window
	initRendering();
	glutDisplayFunc(drawScene);
	glutTimerFunc(10, update, 0);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(handlemouse_drag);
	glutReshapeFunc(handleResize);
	glutTimerFunc(1000, generate, 0);

	glutMainLoop();
	return 0;
}

void play()
{
	system("aplay Sounds/mono.wav &");
}
//////////////////////////////////////// Function to draw objects on the screen///////////////////////////////////////////////////

void drawScene()
{

	if(paused and exit_flag==1)
		exit(0);
	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
	GLvoid *font_style_2 = GLUT_BITMAP_TIMES_ROMAN_24;//fonsts for printing the score board

	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glPushMatrix();


	



	//Draw Mirrors
	glPushMatrix();
	glTranslatef(0.0f,0.0f,z_cord-32.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	//glBegin(GL_QUADS);
	glVertex2f(-1.0f,9.0f);
	glVertex2f(3.0f, 7.0f);
	glVertex2f(3.0f,7.0f);
	glVertex2f(-1.0f,9.0f);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();

	//Draw Mirrors
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-60.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glBegin(GL_POLYGON);
	//glBegin(GL_QUADS);
	glVertex2f(15.0f,-9.0f);
	glVertex2f(17.0f, -5.0f);
	glVertex2f(17.0f,-5.0f);
	glVertex2f(15.0f,-9.0f);
	//glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
	
	// Draw Box
	glTranslatef(2.0f, 0.0f, z_cord);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawBox(box_len);

	//Draw the BASE
	glPushMatrix();
	glTranslatef(-20.0f,-22.0f,z_cord);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(0.0f,0.0f);
	glVertex2f(44.0f, 0.0f);
	glVertex2f(44.0f,4.0f);
	glVertex2f(0.0f,4.0f);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();

	//Draw the Red Basket
	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f,0.6f);
	if(present=='r')
		glColor3f(1.0f,0.0f,0.0f);
	glTranslatef(red_x,red_y, z_cord);
	drawsquare();
	glPopMatrix();

	//Draw Green Basket
	glPushMatrix();
	glColor4f(0.0f,1.0f,0.0f,0.6f);
	if(present=='g')
		glColor3f(0.0f,1.0f,0.0f);;
	glTranslatef(green_x,green_y ,z_cord);
	//   glScalef(0.6f, 0.6f, 0.6f);
	drawsquare();
	glPopMatrix();

	// Draw Cannon
	glPushMatrix();
	glTranslatef(tri_x, tri_y, z_cord);
	//glRotatef(270, 0.0f, 0.0f,1.0f);
	glRotatef(theta, 0.0f, 0.0f,1.0f);
	glColor4f(0.40f,0.40f,0.40f,0.6f);
	if(present=='c')
		glColor3f(0.40f,0.40f,0.40f);	//   glScalef(0.4f, 0.4f, 0.4f);
	drawTriangle();
	glPopMatrix();
	for(it=blocks.begin();it!=blocks.end();++it)
	{
		if(it->state!=2)
		{
			glPushMatrix();
			if(it->sp_col=='r')
			{
				glColor3f(1.0f,0.0f,0.0f);
				glTranslatef(it->sp_x,it->sp_y, z_cord);
				drawsquare1();
			}
			else if(it->sp_col=='b')
			{
				glColor3f(0.0f,0.0f,0.0f);
				glTranslatef(it->sp_x,it->sp_y, z_cord);
				drawsquare1();
			}
			else if(it->sp_col=='g')
			{
				glColor3f(0.0f,1.0f,0.0f);
				glTranslatef(it->sp_x,it->sp_y, z_cord);
				drawsquare1();
			}
			else if(it->sp_col=='y')   //POWER UP BLOCK
			{
				glColor4f(0.5f,0.0f,0.5f,0.43f);
				glTranslatef(it->sp_x,it->sp_y, z_cord);
				drawpower();

			}
			glPopMatrix();
		}
	}

	//////////////////////////////////////////////////////DRAWING THE LASERS/////////////////////////////////////////////////////////////////	
	for(il=lasers.begin();il!=lasers.end();++il)
	{
		if(il->state!=2)
		{
			glPushMatrix();
			glColor3f(1.0f,0.0f,0.0f);
			if(il->hit_state==0)
			{
				glTranslatef(il->x-(sin(DEG2RAD(il->thet))*2.5f),il->y+(cos(DEG2RAD(il->thet))*2.5f),z_cord);
				//glRotatef(270,0.0f,0.0f,1.0f);
				glRotatef(il->thet,0.0f,0.0f,1.0f);
				glBegin(GL_LINES);
				glVertex2f(0.0f,1.0f);
				glVertex2f(0.0f,-1.0f);
				glEnd();
			}
			else
			{
				glTranslatef(il->nx,il->ny,z_cord);
				//glRotatef(270,0.0f,0.0f,1.0f);
				glRotatef(il->thet,0.0f,0.0f,1.0f);
				glBegin(GL_LINES);
				glVertex2f(0.0f,0.0f);
				glVertex2f(0.0f,2.0f);
				glEnd();
			}
			glPopMatrix();
		}
	}

	/////////////////////////////////////////////TO SHOW THE PAUSED SCENE///////////////////////////////////////////////////////////////

	if(paused)
	{
		glPushMatrix();
		glColor3f(1.0f,0.0f,0.0f);
		glRasterPos3f(0.0f,0.0f,z_cord);
		glScalef(5.0f,5.0f,5.0f);
		int k;
		char a[]={"GAME PAUSED"};
		for(k=0;a[k]!='\0';k++)
		{
			glutBitmapCharacter(font_style, a[k]);
		}
		glPopMatrix();
	}
	glPushMatrix();
	glColor3f(1.0f,1.0f,0.0f);
	glTranslatef(-38.0f,16.0f,z_cord);
	glBegin(GL_QUADS);
	glVertex2f(-2,-2);
	glVertex2f(-2, 3);
	glVertex2f(10, 3);
	glVertex2f(10,-2);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos3f(-38.0f,16.0f,z_cord);
	glScalef(5.0f,5.0f,5.0f);
	char b[]={"My Score"};
	char new_sc[1000];
	sprintf(new_sc,"%s %d",b,score);
	int k;
	for(k=0;new_sc[k]!='\0';k++)
	{
		glutBitmapCharacter(font_style_2, new_sc[k]);
	}
	glPopMatrix();
	if(exit_flag==1)
	{
		//system("aplay mono.wav &");
		glPushMatrix();
		glColor3f(1.0f,0.0f,0.0f);
		glRasterPos3f(0.0f,0.0f,z_cord);
		glScalef(5.0f,5.0f,5.0f);
		int k;
		char ttt[]={"GAME OVER"};
		for(k=0;ttt[k]!='\0';k++)
		{
			glutBitmapCharacter(font_style, ttt[k]);
		}
		if(exit_time>2000)
		{
			exit(0);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
////////////////////////////////////////////////UPDATE FUNCTION///////////////////////////////////////////////

void update(int value) 
{
	if(!paused)
	{
		hit_flag+=10;speed_time+=10;power_up+=10;
		if(exit_flag==1)
			exit_time+=10;
		/////////////////////////////////////////////////BLOCKS COLLISION WITH CANON AND BOXES/////////////////////////////////////////////////////

		for(it=blocks.begin();it!=blocks.end();++it)
		{
			if(it->state==0 and it->sp_y<=-18.0f)
			{
				//if(((it->sp_x>=tri_x-2.0f and it->sp_x<=tri_x+1.9f) or (it->sp_x+4.0f>=tri_x-1.9f and it->sp_x+4.0f<=tri_x+2.0f)))
				//{
					//printf("SCORE%d\n",score);
					//if(it->sp_col=='y')
					//{
					//	system("aplay Sounds/tada.wav &");
					//	for(ix=blocks.begin();ix!=blocks.end();++ix)
					//		ix->state=2;
					//}
					if( it->sp_x >-20.0f and it->sp_x<=20.0f  and  it->sp_col=='b' and it->sp_x!=red_x and it->sp_x!=green_x)
					{
						//if(it->sp_col=='b')
						//{
						//	system("aplay mono.wav &");
							play();
							exit_flag=1;
						//}
					}
				//}
				
				else if(it->sp_x==red_x)
				{
					if(it->sp_col=='r')
						score+=5;
					else if(it->sp_col=='g')
						score+=2;
					else if(it->sp_col=='y')
					{
						system("aplay Sounds/tada.wav &");
						for(ix=blocks.begin();ix!=blocks.end();++ix)
							ix->state=2;
						score+=20;
					}
					
					else
						score-=5;
					it->state=2;
				}
				else if(it->sp_x==green_x)
				{
					if(it->sp_col=='g')
						score+=5;
					else if(it->sp_col=='r')
						score+=2;
					else if(it->sp_col=='y')
					{
						system("aplay Sounds/tada.wav &");
						for(ix=blocks.begin();ix!=blocks.end();++ix)
							ix->state=2;
						score+=20;
					}
					else
						score-=5;
					it->state=2;
				}
			
				//////////////////////////////////GAMEOVER//////////////////////////////////////////////////////////////////////////////////
				//if (it->sp_col=='b' and it->sp_y==-18.0f and it->state==2)
				//{
				//	exit_flag=1;
				//}
			}

		
			//////////////////////////////////GAMEOVER//////////////////////////////////////////////////////////////////////////////////
			//if (it->sp_col=='b' && it->sp_y==-18.0f && it->state==2)
			//{
			//	exit_flag=1;
			//}
		}
		//////////////////////////////////ZOOM IN AND OUT ///////////////////////////////////////////////////////////////////////////////

		if((present=='z') && z_cord<=-25.0f)
		{
			z_cord=z_cord+0.5f;
			present='c';
		}
		if ((present=='x') && z_cord>=-31.0f)
		{
			z_cord=z_cord-0.5f;
			present='c';
		}

		//////////////////////////////////SPEEDIN UP THE BLOCKS/////////////////////////////////////////////////////////////////////

		if(speed_time>10000)
		{
			printf("INCREADE\n");
			speed_time=0;
			block_speed+=0.05f;
		}
		if(present=='m')
		{
			block_speed=0.3f;
			present='c';
		}
		else if (present=='n')
		{
			block_speed=0.1f;
			present='c';
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for(it=blocks.begin();it!=blocks.end();++it)
		{
			if(it->state==0)
			{
				if(it->sp_y<=-18.0f)
				{
					//start=-18.0f;end=22.0f;
					if(it->sp_col!='y')
					{
						it->state=1;
						score-=5;
					}
					else
					{
						it->state=2;
					}
				}
				it->sp_y-=block_speed;
			}
		}

		////////////////////////////////////////////////////MOVEMENT OF LASERS///////////////////////////////////////////////////////

		for(il=lasers.begin();il!=lasers.end();++il)
		{
			//printf("%f %f\n", il->thet,cos(DEG2RAD(il->thet)));
			if(il->hit_state==0)
			{
				il->x+=-sin(DEG2RAD(il->thet))*0.4f;
				il->y+=cos(DEG2RAD(il->thet))*0.4f;
			}
			else
			{
				il->nx+=-sin(DEG2RAD(il->thet))*0.4f;
				il->ny+=cos(DEG2RAD(il->thet))*0.4f;
			}
		}

		////////////////////////////////////////////////BLOCK AND LASER COLLISION////////////////////////////////////////////////////////

		for(it=blocks.begin();it!=blocks.end();++it)
		{
			if(it->state==0)
			{
				for(il=lasers.begin();il!=lasers.end();++il)
				{
					if(il->state!=2)
					{
						if(il->hit_state==0)
						{
							if((il->x-sin(DEG2RAD(il->thet))*1.0f)>=it->sp_x && (il->x+sin(DEG2RAD(il->thet))*1.0f)<=it->sp_x+4.0f)
							{
								if((il->y+cos(DEG2RAD(il->thet))*1.0f)>=it->sp_y && (il->y+cos(DEG2RAD(il->thet))*1.0f)<=it->sp_y+4.0f)
								{
									system("aplay Sounds/exp.wav &");

									it->state=2;il->state=2;
									if(it->sp_col=='b')
										score+=5;
									if(it->sp_col=='y')
									{
										score+=10;
										block_speed+=0.05f;
									}
									break;
								}
							}
						}
						else if(il->hit_state==1)
						{
							if((il->nx-sin(DEG2RAD(il->thet))*2.0f)>=it->sp_x && (il->nx+sin(DEG2RAD(il->thet))*2.0f)<=it->sp_x+4.0f)
							{
								if((il->ny+cos(DEG2RAD(il->thet))*2.0f)>=it->sp_y && (il->ny+cos(DEG2RAD(il->thet))*2.0f)<=it->sp_y+4.0f)
								{
									it->state=2;il->state=2;
									break;
								}
							}
						}
					}
				}
			}
		}

		///////////////////////////////////////////////////LASER REFLECTION//////////////////////////////////////////////////////////////


		for(il=lasers.begin();il!=lasers.end();++il)
		{
			if(il->state!=2)
			{
				if(il->hit_state==0)
				{
					if((il->x-sin(DEG2RAD(il->thet))*1.0f)>=box_len+1.0f || (il->x-sin(DEG2RAD(il->thet)))*1.0f<=-19.0f || (((il->x-sin(DEG2RAD(il->thet)))*1.0f<=0.0f and  (il->x-sin(DEG2RAD(il->thet)))*1.0f>-4.0f) and ((il->y-sin(DEG2RAD(il->thet))*1.0f>6.50f) and (il->y-sin(DEG2RAD(il->thet))*1.f<=8.0f))))
					{
						//|| (((il->x-sin(DEG2RAD(il->thet)))*1.0f<=-0.0f and  (il->x-sin(DEG2RAD(il->thet)))*1.0f>-4.0f) and ((il->y-sin(DEG2RAD(il->thet))*1.0f>6.50f) and (il->y-sin(DEG2RAD(il->thet))*1.0f<=8.0f)))
						//il->hit_state=1;
						//	il->nx=il->x;
						il->ny=il->y+cos(DEG2RAD(il->thet))*2.0f;
						if((il->x-sin(DEG2RAD(il->thet))*2.0f)>=box_len+1.0f)
							il->nx=box_len+1.0f-sin(DEG2RAD(il->thet))*2.0f;
						else
							il->nx=-19.0f-sin(DEG2RAD(il->thet))*2.0f;
						il->thet*=-1;		 
					}
				}
			}
		}

		///////////////////////////////////////////////////BLOCKING CONDITION/////////////////////////////////////////////////////////////////

		start=-20.0f;end=22.0f;
		for(it=blocks.begin();it!=blocks.end();++it)
		{
			if(it->state==1)
			{
				if((it->sp_x)>=-20.0f && (it->sp_x+4.0)<=(tri_x))
				{
					temp=(it->sp_x+4.0);
					if(temp>start)
						start=temp;
				}
				if((it->sp_x+2.0f)<=22.0f && (it->sp_x)>=(tri_x))
				{
					temp1=(it->sp_x-2.0f);
					if(temp1<end)
						end=temp1;
				}
			}
		}
	}
	glutTimerFunc(10, update, 0);
}


///////////////////////////////////////////GENERATING BLOCKS//////////////////////////////////////////////////////////////////////////

void generate(int val)
{
	if(!paused)
	{
		fallingblock.sp_x=((rand()%6)*4.0f)-6.0f;
		fallingblock.sp_y=21.0f;fallingblock.state=0;
		int sign=rand()%2;
		if(sign==1)
			fallingblock.sp_x*=-1;
		int c=rand()%4;
		if(c==0)
			fallingblock.sp_col='r';
		else if(c==1)
			fallingblock.sp_col='b';
		else if(c==2)
			fallingblock.sp_col='g';
		else if(c==3 and power_up>10000)
		{
			printf("YELLOW\n");
			power_up=0;
			fallingblock.sp_col='y';
		}		
		blocks.push_back(fallingblock);
	}
	glutTimerFunc(2000, generate, 0);
}

//////////////////////////////////////////////////////MAKING LASERS///////////////////////////////////////////////////////////////

void createlaser()
{
	//	int id=fork();
	//	if(id==0)
	//		execvp(args[0],args);
	system("aplay Sounds/laser.wav &");
	las.x=tri_x;las.y=tri_y;las.thet=theta,las.state=1,las.hit_state=0;
	lasers.push_back(las);
}

///////////////////////////////////////////////////DRAWING OBJECTS///////////////////////////////////////////////////////////////////

void drawBox(float len) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void drawsquare()
{
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glVertex3f(2.0f, 2.0f, 0.0f);
	glVertex3f(4.0f, 3.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

}
void drawpower()
{
	glBegin(GL_QUADS);
	glVertex2f(2,0);
	glVertex2f(4,2);
	glVertex2f(2,4);
	glVertex2f(0,2);
	glEnd();
}
void drawsquare1()
{
	glBegin(GL_QUADS);
	glVertex3f(1.0f, 3.0f, 0.0f);
	glVertex3f(3.0f, 3.0f, 0.0f);
	glVertex3f(3.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	

}
void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_QUADS);
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0,0,0);
	glVertex3f(1.0f, 0.4f, 0.0f);
	glVertex3f(1.2f, 0.4f, 0.0f);
	glVertex3f(1.2f, 0.6f, 0.0f);
	glVertex3f(1.0f, 0.6f, 0.0f);
	//glColor3f(0,0,0);
	glVertex3f(-1.0f, 0.4f, 0.0f);
	glVertex3f(-1.2f, 0.4f, 0.0f);
	glVertex3f(-1.2f, 0.6f, 0.0f);
	glVertex3f(-1.0f, 0.6f, 0.0f);
	//glColor3f(0,0,0);

	glVertex3f(2.0f,2.0f,0.0f);
	glVertex3f(2.0f,-2.0f,0.0f);
	glVertex3f(1.2f,-2.0f,0.0f);
	glVertex3f(1.2f,2.0f,0.0f);

	glVertex3f(-2.0f,2.0f,0.0f);
	glVertex3f(-2.0f,-2.0f,0.0f);
	glVertex3f(-1.2f,-2.0f,0.0f);
	glVertex3f(-1.2f,2.0f,0.0f);

	glVertex3f(-0.33f,2.5f,0.0f);
	glVertex3f(-0.33f,1.0f,0.0f);
	glVertex3f(0.33f,1.0f,0.0f);
	glVertex3f(0.33f,1.5f,0.0f);
	glEnd();
}

// Initializing some openGL 3D rendering options/////////////////////////////////////////////////////
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized/////////////////////////////////////////////////////////////

void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////PAUSE AND QUIT//////////////////////////////////////////////////////////////

void handleKeypress1(unsigned char key, int x, int y) 
{
	if(key==32 and paused==false and hit_flag>=1000)
	{
		hit_flag=0;
		createlaser();
	}
	else if (key == 27 or key=='q') {
		exit(0);     // escape key is pressed
	}
	if(key=='c' and paused==false)
	{
		present='c';
		printf("%c\n",present );
	}
	else if(key=='g' and paused==false)
		present='g';
	else if(key==114 and paused==false)
		present='r';
	else if(key=='p')
	{
		printf("Pause\n");
		paused=!paused;
	}
	else if(key=='m' and paused==false)
		present='m';
	else if(key=='n' and paused==false)
		present='n';
	else if(key=='z')
		present='z';
	else if(key=='x')
		present='x';
}

//////////////////////////////////////////////////BOX AND CANNON MOVEMENT////////////////////////////////////////////////////////

void handleKeypress2(int key, int x, int y) 
{
	if(!paused)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if(present=='c'&& tri_y-2.0f>-18.0f )
				tri_y -= 1.0;
			else if(present=='r'&& red_x>-20.0f && red_x<=20.0f)
				red_x-=1.0;
			else if(present=='g'&& green_x>-20.0f && green_x<=20.0f)
				green_x-=1.0;
		}
		else if (key == GLUT_KEY_RIGHT)
		{
			if(present=='c' && tri_y<20.0f)
				tri_y += 1.0;
			else if(present=='r'&& red_x>=-20.0f && red_x<20.0f)
				red_x+=1.0;
			else if(present=='g'&& green_x>=-20.0f && green_x<20.0f)
				green_x+=1.0;
		}
		else if((key==GLUT_KEY_DOWN || key=='d') && (theta-270)>-50 )
			theta-=10;
		else if((key==GLUT_KEY_UP || key=='a') && (theta-270)<50 )
			theta+=10;
		else if (key=='s')
		{
			if( tri_y<20.0f )
				tri_y += 1.0;
		}
		else if(key=='f')
		{
			if( tri_y-2.0f>-18.0f )
				tri_y -= 1.0;
		}

	}

}

//////////////////////////////////////////////GENERATES MOUSE COORDINATES////////////////////////////////////////////////

void GetOGLPos(int x, int y)
{
	if(!paused)
	{
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;
		GLdouble posX, posY, posZ;

		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		glGetDoublev( GL_PROJECTION_MATRIX, projection );
		glGetIntegerv( GL_VIEWPORT, viewport );

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

		gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		mouseposx=posX*1000*18/32.0;
		mouseposy=posY*1000*21/38.0;
		mouseposz=0;
	}
}

///////////////////////////////////////////DRAGGING MOUSE FOR MOVING OBJECTS///////////////////////////////////////////////////

void handlemouse_drag(int x,int y)
{
	if(!paused)
	{
		GetOGLPos(x, y);
		if(click==1)
		{
			if(present=='c' &&  mouseposy>-16.0f && mouseposy<20.0f)
			{
				tri_y=mouseposy;
			}
			else if(present=='g' && (mouseposx)<20.0f && mouseposx>-20.0f)
			{
				green_x=mouseposx;
			}
			else if(present=='r' && (mouseposx)<20.0f && mouseposx>-20.0f)
			{
				red_x=mouseposx;
			}
		}
		else if (click==2)
		{      
			present='c';
			float s1=mouseposx-tri_x;
			float s2=mouseposy-tri_y;
			float temp_angle=-atan(float(s1)/s2)*180/PI;
			if(temp_angle>=-60 && temp_angle<=60)
			{
				theta=-atan(float(s1)/s2)*180/PI;
			}
		}
	}
}

///////////////////////////////////////////////SELECTING OBJECTS BY MOUSE///////////////////////////////////////////////

void handleMouseclick(int button, int state, int x, int y) 
{
	if(!paused)
	{

		if (state == GLUT_DOWN)
		{
			if (button == GLUT_LEFT_BUTTON)
			{  
				if(theta>-50 and theta<50) 
					theta += 10;
				click=1;
				GetOGLPos(x,  y);
				//float x1=tri_x-2.0f;
				//float x2=tri_x+2.0f;
				//float y1=tri_y-2.0f;
				//float y2=tri_y+2.0f;
				//cout<<mouseposx<<" "<<mouseposy<<" "<<mouseposz<<" "<<" "<<tri_x<<" "<<tri_y<<endl; 
				//SSif(mouseposx>=x1 && mouseposx<=x2 && mouseposy>=y1 &&  mouseposy<=y2 )
				//	present='c';
				float x11=green_x;
				float x22=green_x+4.0f;      
				float y11=green_y;
				float y22=green_y+3.0f;
				if(mouseposx>=x11 && mouseposx<=x22 && mouseposy>=y11 &&  mouseposy<=y22 )
					present='g';
				float x111=red_x;
				float x222=red_x+4.0f;       
				float y111=red_y;
				float y222=red_y+3.0f;
				if(mouseposx>=x111 && mouseposx<=x222 && mouseposy>=y111 &&  mouseposy<=y222 )
					present='r';
			}
			else if (button == GLUT_RIGHT_BUTTON)
			{
				click=2;
			}
		}
		else if (button==3)
		{
			present='z';
		}
		else if(button==4)
		{
			present='x';
		}
		else
		{
			present='c';
		}
	}
}

