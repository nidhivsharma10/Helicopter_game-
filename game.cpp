#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<stdio.h>
float block_speed=0.002; 
float block1_x=50.0 ,block1_y=0;
float heli_m=0.0;
int i=0,score_Int=1;
float score_Float=1; 
int level=1, lflag=1, wflag=1; 
char score_String[20] ,level_string[20];
void init(void)
{
srand(time(0));
block1_y=(rand()%45)+10;//b/w 10 to 44
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_SMOOTH);
glLoadIdentity ();
glOrtho(0.0, 100.0, 0.0, 100.0, -1.0 , .0);
}
void draw_Helicopter()
{
glColor3f(0.7,1.0,1.0);
glRectf(10,49.8,19.8,44.8);
glRectf(2,46,10,48);
glRectf(14,49.8,15.8,52.2);
glRectf(7,53.6,22.8,52.2);
}
void renderBitmapString(float x,float y,float z,void *font,char*string)
{
char *c;
glRasterPos3f(x, y,z);
for(c=string; *c != '\0'; c++)
{
glutBitmapCharacter(font, *c);
}
}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT);
// Checking GameOver
if((i==730||i==-700)
//top and bottom checking
||
( ((int)block1_x==10||(int)block1_x==7||(int)block1_x==4||(int)block1_x==1) &&(int)block1_y<53+(int)heli_m&&(int)block1_y+35>53+(int)heli_m)
// propeller front checking
||
( ((int)block1_x==9||(int)block1_x==3||(int)block1_x==6) &&(int)block1_y<45+(int)heli_m&&(int)block1_y+35>45+(int)heli_m)
{
glColor3f(0.0,0.0,1.0);
glRectf(0.0,0.0,100.0,100.0);
glColor3f(1.0,0.0,0.0);
glColor3f(1.0,1.0,1.0);
glutSwapBuffers();
glFlush();
printf("\nGAME OVER !!!\n\n");
printf("\n\nClose the console window to exit...\n");
exit(0);
}
else if(wflag==1)
{
wflag=0;
glColor3f(0.0,0.5,0.7);
glRectf(0.0,0.0,100.0,10.0);//ceil
glRectf(0.0,100.0,100.0,90.0);//floor
glColor3f(1.0,1.0,1.0);
glColor3f(1.0,1.0,0.0);
glColor3f(1.0,0.0,0.0);
renderBitmapString(43,30,0,GLUT_BITMAP_TIMES_ROMAN_24,"Click To Start");
renderBitmapString(17,24,0,GLUT_BITMAP_9_BY_15,"CLICK AND HOLD LEFT MOUSE BUTTON TO GO UP RELEASE TO GO DOWN");
glColor3f(0.0,0.0,0.0);
draw_Helicopter();
glutSwapBuffers();
glFlush();
}
else
{
if(score_Int%50!=0 &&  lflag!=1)
{
lflag=1;
}
glPusheli_matrix();
glColor3f(0.0,0.5,0.7);
glRectf(0.0,0.0,100.0,10.0); //ceil
glRectf(0.0,100.0,100.0,90.0); //floor
glColor3f(0.0,0.0,0.0); //score
score_Float+=0.050; 
score_Int=(int)score_Float;
glTranslatef(0.0,heli_m,0.0);
draw_Helicopter();
if(block1_x<-10)
{
block1_x=50; //total width is 50
block1_y=(rand()%25)+20;
}
else
block1_x-=block_speed;
glTranslatef(block1_x,-heli_m,0.0);
glColor3f(1.0,0.0,0.0);
glRectf(block1_x,block1_y,block1_x+5,block1_y+35);//block 1
glPopMatrix();
glutSwapBuffers();
glFlush();
}
}
void moveHeliU(void)
{
heli_m+=0.05;
i++;
glutPostRedisplay();
}
void moveHeliD()
{
heli_m-=0.05;
i--;
glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
switch (button)
{
case GLUT_LEFT_BUTTON:
if (state == GLUT_DOWN)
glutIdleFunc(moveHeliU);
else if (state == GLUT_UP)
glutIdleFunc(moveHeliD);
break;
default: break;
}
}
void keys(unsigned char key,int x,int y)
{
if(key=='w') glutIdleFunc(moveHeliU);
if(key=='m') glutIdleFunc(moveHeliD);
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize (800, 600);
glutInitWindowPosition (200,200);
glutCreateWindow ("2D Copter Game");
init();
glutDisplayFunc(display);
glutMouseFunc(mouse);
glutMainLoop();
return 0;
}
