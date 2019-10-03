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
	glPushMatrix();
	glTranslatef(x, y, z);
	//glRotatef(angle, x, y, z); // in this one, the pot will self-rotate while do up-right
	glRotatef(angle, 0, 0, 1);
	glutSolidTeapot(size);
	glPopMatrix();
}


void problem1() {

	// TODO: Your code here!
	// I choose this code because it looks like the requirement, but I prefer the one in the comment
	//this code is for only this specific case 1
	GLfloat size = 0.2;
	float pi = 3.14;
	GLfloat xarray[10] = { cos(0), cos(pi / 6) , cos(pi / 3), cos(2*pi/3), cos( 5*pi/6),
	                      cos(pi), cos(7*pi/6), cos(4*pi/3), cos(5*pi/3), cos(11*pi/6) };
	GLfloat yarray[10] = { sin(0), sin(pi / 6) , sin(pi / 3), sin(2*pi/3), sin( 5*pi/6),
	                      sin(pi), sin(7*pi/6), sin(4*pi/3), sin(5*pi/3), sin(11*pi/6) };
	GLfloat angle [10] = {0, 30, 60, 120, 150, 180, 210, 240, 300, 330};

	for (int i = 0; i < 10; i++) {
	 rotatePot(xarray[i]*1.5, yarray[i]*1.5, 0, size, angle[i]);
	}

	/*
	//this section is for general case, easy to adjust
	float pi = 3.1415;
	GLfloat size = 0.22;
	GLfloat angle = 0;
	GLfloat angle2 = 0;
	GLfloat add = pi / 6;
	GLfloat x, y, z;
	while (angle < 12*add) {
		if ((angle != (3*add)) && (angle != (9*add))) {
			z = 0;
			x = cos(angle);
			y = sin(angle);
			rotatePot(x, y, z, size, angle2);
		}
		angle += add;
		angle2 += 30;
	}
	*/
}
//function drawCollumn is used in problem2()
void drawCollumn( GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height) {
	/*Input: x,y,z - cordinate for function glTranslatef(), moving the column to assigned location
	         width, height - the numerical values to scale the glutSolidCube() function, creating a pillar instead of a cube
	  Output: nothing
	  Function: drawing a cube with scale (width, height, length) at (x,y,z)*/
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(width, height, width );
	glutSolidCube(1);
	glPopMatrix();



 }

void problem2() {
	// TODO: Your code here!

	//values to scale the cubes
	GLfloat width = 0.2;  // the width and length of the cubes
	GLfloat height = 0.1; //the height of the cubes, increasing
	//The cordinates
	GLfloat xfirst = -2; //the first location of x
	GLfloat dif = 0.04; //the difference in height between two adjacent collumns
	GLfloat addDif = dif/2; //use addDif to help all collumns stay equally on a flat surface
	GLfloat xlate = 2; //the end of the line
	GLfloat yfirst = 0; //the first value of y =0, the first box
	//while run from xfirst to xlate x(-2, 2)
	while (xfirst < xlate) 
	{
		drawCollumn(xfirst, yfirst, 0, width, height); //draw a cube on xOy surface, z=0
		xfirst += width; //each cube-center is |width| unit from each other on x-axis
		yfirst += addDif; //add 1/2 the difference in height to help all cubes stay on one surface
		height += dif; //increase the height
	}	
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
	GLfloat xfirst = 0;
	GLfloat yfirst = 0.75;
	//the size for each teapot
	GLfloat size = 0.1;
	//the (xmov, ymove) is coordinate of each teapot-i, the teapot-1 has cordinate (0, 0.75, 0)
	GLfloat xmov = xfirst;
	GLfloat ymov = yfirst;
	//yw-xw: use inside the while-loop
	GLfloat xw, yw;
	int cal = 0; //use to locate the odd and even row on the eramic
	//draw the first teapot at the peak
	transTeapot(xfirst, yfirst, 0, size);
	//Do while loop, while x < 1.5, in the line y = 0.75 - x
	while (xmov <= (2 * yfirst )) {
		ymov = ymov - 2*size; //decrease y by 2 time the size of teapot- new ymov
		xmov = yfirst - ymov; //calculate the new xmov from ymov
		//If the row is even
		if (cal == 0) {
			xw = 2*size; //begin drawing from the location (2*size, ymov,0) and the symetric counterpart
			yw = ymov;
			transTeapot(xw, yw, 0, size);
			transTeapot(-xw, yw, 0, size);
			cal = 1;
		}
		else
		{//if the row is odd
			xw = 0;
			yw = ymov;
			transTeapot(xw, yw, 0, size); //begin drawing at the center of the row
			cal = 0;
		}
		while (xw <= xmov) {
			xw = xw + 4 * size;
			if (xw > xmov) //to avoid drawing outside of the line
			{
				transTeapot(xmov, yw, 0, size);
				transTeapot(-xmov, yw, 0, size);
			}
			else
			{//draw teapot in two sides of the row
				transTeapot(xw, yw, 0, size);
				transTeapot(-xw, yw, 0, size);
			}	
		}	
	}
}
void drawStar(GLfloat x, GLfloat y,  GLfloat distance)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x, y);
	glVertex2f(x + 1 / 2 * distance, y + 3 / 2 * distance);
	
	glVertex2f(x, y + distance);
	glVertex2f(x + distance, y);
	glVertex2f(x + distance, y + distance);

	glEnd();

}
void problem4() {
	// TODO: Your code here!
	//twist
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.4, 0.0);
	glVertex3f(-0.1, -0.25, 0.0);
	glVertex3f(0.1, -0.25, 0.0);
	glVertex3f(0.1, -0.4, 0.0);
	glEnd();
	glPopMatrix();
	//thumb finger
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.25, 0.0);
	glVertex3f(0.15, -0.1, 0.0);
	glVertex3f(0.08, 0.0, 0.0);
	glVertex3f(0.0, -0.05, 0.0);
	glVertex3f(-0.05, -0.1, 0.0);
	glVertex3f(0.07, -0.1, 0.0);
	glVertex3f(0.1, -0.2, 0.0);
	glEnd();
	glPopMatrix();
	//pointy finger and middle finger
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.08, 0.0, 0.0);
	glVertex3f(0.1, -0.05, 0.0);
	glVertex3f(0.15, 0.2, 0.0);
	glVertex3f(0.1, 0.2, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(-0.1, 0.2, 0.0);
	glVertex3f(-0.15, 0.2, 0.0);
	glVertex3f(-0.1, 0.05, 0.0);
	glVertex3f(0.0, -0.1, 0.0);
	glEnd();
	glPopMatrix();
	//ring finger
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0.05, 0.0);
	glVertex3f(0.0, -0.1, 0.0);
	glVertex3f(-0.03, -0.13, 0.0);
	glVertex3f(-0.15, 0.03, 0.0);
	glEnd();
	glPopMatrix();
	//final fingr
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.03, 0.0);
	glVertex3f(-0.2, 0.0, 0.0);
	glVertex3f(-0.1, -0.15, 0.0);
	glVertex3f(-0.07, -0.14, 0.0);
	glEnd();
	glPopMatrix();
	//complete the hand
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.1, 0.0);
	glVertex3f(-0.1, -0.25, 0.0);
	glEnd();
	glPopMatrix();

	
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
