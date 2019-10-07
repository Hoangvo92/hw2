/*******************************************************
 * Homework 2: OpenGL                                  *
 * CS 148 (Summer 2016), Stanford University           *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
//my include of library



#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = { 0,1,4,1 };
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };


void rotatePot(GLfloat x, GLfloat y, GLfloat z, GLfloat size, GLfloat angle) {
	/*Input: x,y,z - the cordinate of the teapot
	         size - the size of the teapot
			 angle - the rotated angle of the teapot around the z-xis, in degree
			         for the glRotatef
	output: nothing
	function: draw the teapot with rotated angle around z-axis
	*/
	glPushMatrix();
	//locate the location of the the teapot
	glTranslatef(x, y, z);
	//glRotatef(angle, x, y, z); // in this one, the pot will self-rotate  around z-axis, x-axis, and y-axis
	//rotate with the assigned angle, (x,y,z)=(0,0,1)->rotate around z-xis
	glRotatef(angle, 0, 0, 1);//the angle is in degree, not radian
	glutSolidTeapot(size);//draw teapot
	glPopMatrix();
}


void problem1() {
	/*Input: nothing
	  output: nothing
	  function: draw just like a picture
	*/
	// TODO: Your code here!

	//declare pi
	float pi = 3.1415f;
	//assign a random size for the teapot
	GLfloat size = 0.22f;
	//the first angle in both radian and degree
	GLfloat angle = 0.0f;
	GLfloat angle2 = 0.0f;
	//the different angle between each teapot= 2/10*pi= 1/5*pi=1/5*180
	GLfloat add = pi / 5;
	GLfloat add2 = (180.0f / 5);//for the glRotatef()
	//the dummy variables to store cordinate of each teapot
	GLfloat x, y, z=0;
	while (angle < 2*pi) {
		x = cos(angle); //calculate value of x-ordinate
		y = sin(angle); //calculate value of y-ordinate
		rotatePot(x, y, z, size, angle2);//call out the function
		angle += add;//increase angle in radian
		angle2 += add2;//increase the angle in degree
	}
	return;
}
//function drawCollumn is used in problem2()
void drawCollumn( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height) {
	/*Input: x,y,z - cordinate for function glTranslatef(), moving the column to assigned location
	         width, height - the numerical values to scale the glutSolidCube() function, creating a pillar instead of a cube
	  Output: nothing
	  Function: drawing a cube with scale (width, height, length) at (x,y,z)*/
	glPushMatrix();
	glTranslatef(x, y, z);//put the collumn at the location (x, y, z)
	glScalef(width, height, width ); //scale the cube into collumns
	glutSolidCube(1);
	glPopMatrix();

 }

void problem2() {
	// TODO: Your code here!

	//values to scale the cubes
	GLfloat width = 0.2f;  // the width and length of the cubes
	GLfloat height = 0.1f; //the height of the cubes, increasing
	//The cordinates
	GLfloat xfirst = -2.0f; //the first location of x
	GLfloat dif = 0.04f; //the difference in height between two adjacent collumns
	GLfloat addDif = dif/2; //use addDif to help all collumns stay equally on a flat surface
	GLfloat xlate = 2.0f; //the end of the line
	GLfloat yfirst = 0.0f; //the first value of y =0, the first box
	//while run from xfirst to xlate x(-2, 2)
	while (xfirst < xlate) 
	{
		drawCollumn(xfirst, yfirst, 0.0f, width, height); //draw a cube on xOy surface, z=0
		xfirst += width; //each cube-center is |width| unit from each other on x-axis
		yfirst += addDif; //add 1/2 the difference in height to help all cubes stay on one surface
		height += dif; //increase the height
	}	
	return;
}

void transTeapot(GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
	/*
	Input: x, y, z - the input information for coordinate location
	       size - the size of the
	Output: Nothing
	Function: draw a teapot at a certain size at the location (x,y,z)*/
	glPushMatrix(); //open and end with glPushMatrix-glPopMatrix
	glTranslatef(x, y, z); //move to the location (x,y,z)
	glutSolidTeapot(size); //draw the teapot
	glPopMatrix();
}

void problem3() {
	// TODO: Your code here!
	//the cordinate of the peak teapot-constant
	GLfloat xfirst = 0.0f;
	GLfloat yfirst = 0.75f;
	//the size for each teapot
	GLfloat size = 0.1f;
	//the (xmov, ymove) is coordinate of each teapot-i, the teapot-1 has cordinate (0, 0.75, 0)
	GLfloat xmov = xfirst;
	GLfloat ymov = yfirst;
	//yw-xw: use inside the while-loop
	GLfloat xw, yw;
	int cal = 0; //use to locate the odd and even row on the eramic
	//draw the first teapot at the peak
	transTeapot(xfirst, yfirst, 0.0f, size);
	//Do while loop, while x < 1.5, in the line y = 0.75 - x
	while (xmov <= (2 * yfirst )) {
		ymov = ymov - 2*size; //decrease y by 2 time the size of teapot- new ymov
		xmov = yfirst - ymov; //calculate the new xmov from ymov
		//If the row is even
		if (cal == 0) {
			xw = 2*size; //begin drawing from the location (2*size, ymov,0) and the symetric counterpart
			yw = ymov;
			transTeapot(xw, yw, 0.0f, size);
			transTeapot(-xw, yw, 0.0f, size);
			cal = 1;
		}
		else
		{//if the row is odd
			xw = 0.0f;
			yw = ymov;
			transTeapot(xw, yw, 0.0f, size); //begin drawing at the center of the row
			cal = 0;
		}
		while (xw <= xmov) {
			xw = xw + 4 * size;
			if (xw > xmov) //to avoid drawing outside of the line
			{
				transTeapot(xmov, yw, 0.0f, size);
				transTeapot(-xmov, yw, 0.0f, size);
			}
			else
			{//draw teapot in two sides of the row
				transTeapot(xw, yw, 0.0f, size);
				transTeapot(-xw, yw, 0.0f, size);
			}	
		}	
	}
	return;
}
//function to draw the wing-sign of victory
void drawVictory(GLfloat x, GLfloat y,  GLfloat distance)
{
	/*Input: the (x,y) coordinate of the center of the wing
	         distance- a numerical measure to locate other points of the wing
	  output: nothing
	  function: draw a pair of wings*/
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x + distance, y + 1.5 * distance, 0.0f);
	glVertex3f(x + 2 * distance, y - 0.5 * distance, 0.0f);
	glVertex3f(x + distance, y + 1.5 * distance-0.05, 0.0f);
	glVertex3f(x, y - 0.05, 0.0f);
	glVertex3f(x - distance, y + 1.5 * distance - 0.05, 0.0f);
	glVertex3f(x - 2 * distance, y - 0.5 * distance, 0.0f);
	glVertex3f(x -  distance, y + 1.5 * distance, 0.0f);
	glEnd();
	

}
//function to draw hand part 1
void part1() {
	//twist
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, -0.4f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.1f, -0.4f, 0.0f);
	glEnd();
}
//function to draw hand part 2
void part2() {
	//thumb finger
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1f, -0.25f, 0.0f);
	glVertex3f(0.15f, -0.1f, 0.0f);
	glVertex3f(0.08f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.05f, 0.0f);
	glVertex3f(-0.05f, -0.1f, 0.0f);
	glVertex3f(0.07f, -0.1f, 0.0f);
	glVertex3f(0.1f, -0.2f, 0.0f);
	glEnd();
}
//functio to draw hand part 3
void part3() {
	//pointy finger and middle finger
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.08f, 0.0f, 0.0f);
	glVertex3f(0.1f, -0.05f, 0.0f);
	glVertex3f(0.15f, 0.2f, 0.0f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.1f, 0.2f, 0.0f);
	glVertex3f(-0.15f, 0.2f, 0.0f);
	glVertex3f(-0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glEnd();
}
//function to draw hand part 4
void part4() {
	//ring finger
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1f, 0.05f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(-0.03f, -0.13f, 0.0f);
	glVertex3f(-0.15f, 0.03f, 0.0f);
	glEnd();
}
//function to draw hand part 5
void part5() {
	//final finger
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15f, 0.03f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(-0.1f, -0.15f, 0.0f);
	glVertex3f(-0.07f, -0.14f, 0.0f);
	glEnd();

	//complete the hand
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15f, -0.1f, 0.0f);
	glVertex3f(-0.1f, -0.25f, 0.0f);
	glEnd();
}
void problem4() {
	// TODO: Your code here!
	//Note: problem2 can affect the default color setting
	//draw the hand with V sign
	glPushMatrix();
	//glColorMaterial(GL_FRONT, GL_DIFFUSE);
	//glEnable(GL_COLOR_MATERIAL);  //not solving the influence of problem 2
	glPixelTransferf(GL_RED_BIAS, 0.1);
	part1(); part2(); part3(); part4(); part5();
	//draw victory
	drawVictory(0.0f, 0.5f, 0.5f);
	glPopMatrix();
	glFlush();

}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0); // x axis
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0); // y axis
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, windowWidth, windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot, 0, 1, 0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0]) * .1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1, (y - lastPos[1]) * .1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key - '0';
	if (key == 'q' || key == 'Q' || key == 27) {
		exit(0);
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
