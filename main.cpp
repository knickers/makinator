//
// 3D Animation of several 3D
// printer designs
// Nick Cox
// Started April 2012
//
// Glut32 Start-Up Template
// Created by Bart Stander
// Modified and enhanced by Nick Cox
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;
#include <GL/glut.h>
#include "graphics.h"
#include "save.h"
#include "shapes.h"
#include "slider.h"
#include "colors.h"
#include "printer.h"

double gX = 1024;//720;//480;// Width of the screen
double gY = 680; //480;//320;// Height of the screen
bool gAxis = 0;
//Global Variables for Camera
double EYE[3];             // Position of camera
double AT[3] = {0, 0, 0};  // Looking AT point for camera
double UP[3];              // Up vector for camera
double gUpAngle   = PI/7;  // Sphere coordinates of camera //PI/14;
double gPanAngle  = PI*3/2;// Sphere coordinates of camera //PI*5/4;
double gCamAmount = PI/56; // Ammount the camera moves on a key press
double gDist      = 36;    // Camera distance from the origin
double gZoom      = 40;    // Zoom angle, half on each side
double gNear      = 100;   // Near cutpff plane
double gFar       = 500;   // Far cutoff plane
double dX         = 0;     // Delta X for mouse panning
double dY         = 0;     // Delta Y for mouse panning
bool   gGrabbedLeft  = false; // If scene is grabbed by left mouse button
bool   gGrabbedRight = false; // If scene is grabbed by right mouse button
verticalSlider gZoomSlider(0,0,10,100);
// 3d Printer
Printer gPrinter;
double gSpeed = 1;

//Functions difinitions
//**** User code ****
void display(void);
void keyboard(unsigned char c, int x, int y);
void specialKeys(int key, int x, int y);
void mouseClick(int mouse_button, int state, int x, int y);
void mouseDrag(int x, int y);
void mouseMove(int x, int y);
void mouseWheel(int button, int dir, int x, int y);
void idle(void);
void InitializeMyStuff();
//**** Permanent code ****
//void SaveAnim(int frames);
void animationFrame(unsigned ms);
void MoveCamera();
void rightVector(double v[]);
void text_output(double x, double y, const char *string);
void stroke_text(double x, double y, int scale, int rotate, string string);
void number_output(double x, double y, double num);
void stroke_number(double x, double y, int scale, int rotate, double num);
int  random(int low, int high);
void reshape(int w, int h);
void Set2DView();
void Set3DView();
double GetFPS();
double GetFramesPerSecond();

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gX, gY);
	glutInitWindowPosition(10, 10);
	
	bool fullscreen = 0;
	if (fullscreen) {
		glutGameModeString("1280x800:32");
		glutEnterGameMode();
	} else {
		glutCreateWindow("3D Printer"); // Title of the window
	}
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseDrag);
	glClearColor(1,1,1, 0); // Background color
	
	InitializeMyStuff();
	glutMainLoop();
	return 0;
}

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/**************************************************************************/
	Set3DView();                    // 3D VIEW
	/**************************************************************************/
	if (gAxis) {
		DrawAxis(gPrinter.GetSize(), red, green, blue);
	}
	static double r=0, x, y, z;
	if (!gPrinter.Pause()) {
		x = cos(dtor(r))/2 + 0.5;
		y = sin(dtor(r))/2 + 0.5;
		z = cos(dtor(r/2))/2 + 0.5;
		r += gSpeed;
		gPrinter.Set(x,y,z);
	}
	
	gPrinter.Draw();
	
	/**************************************************************************/
	Set2DView();                    // 2D View
	/**************************************************************************/
	glColor3d(0,0,0);
	text(5, gY-15, gPrinter.Title());
	text(5, 5, "Options: " + gPrinter.Options());
	
	/**************************************************************************/
	glutSwapBuffers();          // Display The Scene
	/**************************************************************************/
	if (!gPrinter.Pause() && gSpeed != 0) {
		// Give the processor a break
		SLEEP(20);
//		animationFrame(20);
		// Loop over the display function
		glutPostRedisplay();
	}
	/*
	Save();
	if (r > 720) {
		exit(0);
	}
	*/
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y) {
	if (c >= '1' && c <= '9' ) { // 100-900mm ~ 4-36in printer
		gPrinter.SetSize((c-'0')*100);
	}
	switch (c) {
		case 27: // escape character to quit the program
			exit(0);
			break;
		case 9: // tab
			gAxis = !gAxis; // a to show axis
			break;
		case 'a': // Printer option a
		case 'b': // Printer option b
		case 'c': // Printer option c
			gPrinter.Option(c);
			break;
		case 32: // space to pause
		case 'p': // p to pause
			gPrinter.Pause(!gPrinter.Pause());
			break;
		case '!': // 1, Joint Corner
			gPrinter.SetType(1);
			break;
		case '@': // 2, Cross Corner
			gPrinter.SetType(2);
			break;
		case '#': // 3, Makinator v0
			gPrinter.SetType(3);
			break;
		case '$': // 4, Makinator v1
			gPrinter.SetType(4);
			break;
		case '%': // 5, Makinator v2
			gPrinter.SetType(5);
			break;
		case '^': // 6, Ordbot
			gPrinter.SetType(6);
			break;
		case '0': // 0, 1000mm(40in) printer
			gPrinter.SetSize(1000);
			break;
		case '_': // -, 1200mm(48in) printer
			gPrinter.SetSize(1200);
			break;
		case '<':
		case ',':
			gSpeed -= 0.25;
			break;
		case '>':
		case '.':
			gSpeed += 0.25;
			break;
		case 's': // Save a screenshot
			Save();
			break;
		case '-': // -
			gZoomSlider.Increment(-0.05);
			break;
		case '+': // +
		case '=': // =
			gZoomSlider.Increment(0.05);
			break;
		case 13: // enter
			break;
		default:   // Break instead of return because we still want the camera
			break; // updated when the number keys are pressed
	}
	MoveCamera();
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			gUpAngle += gCamAmount;
			break;
		case GLUT_KEY_RIGHT:
			gPanAngle += gCamAmount;
			break;
		case GLUT_KEY_DOWN:
			gUpAngle -= gCamAmount;
			break;
		case GLUT_KEY_LEFT:
			gPanAngle -= gCamAmount;
			break;
		default:
			return;
	}
	MoveCamera();
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouseClick(int mouse_button, int state, int x, int y) {
	y = gY - y;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(!gGrabbedRight) {
			dX = x;
			dY = y;
			gGrabbedLeft = true;
		}
	} else if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		gGrabbedLeft = false;
	} else if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if(!gGrabbedLeft) {
			dX = x;
			dY = y;
			gGrabbedRight = true;
		}
	} else if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		gGrabbedRight = false;
	}
	MoveCamera();
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever any mouse button is drug.
void mouseDrag(int x, int y) {
	y = gY - y;
	if(gGrabbedLeft) {
		if (gUpAngle > PI/2 && gUpAngle < 3*PI/2) {
			gPanAngle += (x-dX)*gDist/10000;
		} else {
			gPanAngle -= (x-dX)*gDist/10000;
		}
		gUpAngle  -= (y-dY)*gDist/10000;
		if (gUpAngle > 2*PI)  gUpAngle -= 2*PI;
		if (gUpAngle < 0)     gUpAngle += 2*PI;
		if (gPanAngle > 2*PI) gPanAngle -= 2*PI;
		if (gPanAngle < 0)    gPanAngle += 2*PI;
		dX=x;
		dY=y;
	} else if (gGrabbedRight) {
		double right[3];
		rightVector(right);
//		printf("<%f, %f, %f>\n", right[0], right[1], right[2]);
		double lx = dX - x;
		double ly = dY - y;
		for (int i=0; i<3; i++) {
			AT[i] += lx * right[i];
			AT[i] += ly * UP[i];
			EYE[i] += lx * right[i];
			EYE[i] += ly * UP[i];
		}
		dX=x;
		dY=y;
	}
	MoveCamera();
	glutPostRedisplay();
}

// Initialization code goes here.
void InitializeMyStuff() {
	// Init Slider Bars
	gZoomSlider.SetType(SLIDER_BLOCK);
	gZoomSlider.SetColor(.5,.5,.5);
	gZoomSlider.SetValue(.80);
	// Init Printer
	gPrinter.InitDisplayLists();
	gPrinter.Set(0.5, 0.5, 0.5);
	// Init Camera Position
	MoveCamera();
	// Set material's specular properties
	float mat_specular[] = {0.5, 0.5, 0.5, 1};
	float mat_shininess[] = {25};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// Set light properties
	float light_position[] = {0, 0, 300, 1}; // right(x), forward(y), up(z), alpha(transparancy)
	float white_light[] = {1, 1, 1, 1};
	float low_light[] = {.2, .2, .2, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//first light's position
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  white_light);   //first light's full color
	glLightfv(GL_LIGHT0, GL_SPECULAR, low_light);     //first light's shadow color
}

//****************************************************************************//
//****************************************************************************//
//****************************** Permanent Code ******************************//
//****************************************************************************//
//****************************************************************************//

/*void SaveAnim(int frames) {
	static int count = 0;
	Save("ppm");
	count++;
	if(count > frames)
		exit(0);
}*/

void animationFrame(unsigned int ms) {
	static clock_t start = clock();
	unsigned int renderTime = (clock() - start)/1000;
	unsigned int sleepTime = ms - renderTime;
//	printf("clock: %d, renderTime: %d, sleepTime: %d\n", clock(), renderTime, sleepTime);
//	fflush(stdout);
	SLEEP(sleepTime); // sleep time = desired time - render time
//	printf("Done Sleeping\n");
//	fflush(stdout);
	start = clock();
}

void MoveCamera() {
	double prntr = gPrinter.GetSize();
	double table = prntr > 750 ? prntr : 750;
	// Set near and far planes
	double dist = (1-gZoomSlider.GetValue()) * 75 * gDist + 2;
	gFar  = dist + table;
	gNear = dist - table;
	if (gNear <= 0)
		gNear = 0.01;
	
	// Set camera position
	SpherePoint(dist, gUpAngle, gPanAngle, EYE);
	
	// Set up position
	double right[3], forward[3];
	rightVector(right);
	forward[0] = AT[0] - EYE[0];
	forward[1] = AT[1] - EYE[1];
	forward[2] = AT[2] - EYE[2];
	CrossProduct(right, forward, UP);
	for(int i=0; i<3; i++)
		UP[i] /= dist;
}

void rightVector(double v[]) {
	v[0] = cos(gPanAngle + PI/2);
	v[1] = sin(gPanAngle + PI/2);
	v[2] = 0;
}

// Outputs a string of text at the specified location.
void text_output(double x, double y, const char *string) {
	void *font = GLUT_BITMAP_9_BY_15;
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]);
	
	glDisable(GL_BLEND);
}

void text(double x, double y, string str) {
	void *font = GLUT_BITMAP_9_BY_15;
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glRasterPos2d(x, y);
	for (unsigned i = 0; i < str.length(); i++)
		glutBitmapCharacter(font, str[i]);
	
	glDisable(GL_BLEND);
}

// Outputs text to the screen in 'stroke' format
void stroke_text(double x, double y, int scale, int rotate, string string) {
	void *font = GLUT_STROKE_ROMAN;
	int length = (int) string.size();
	glPushMatrix();
		glTranslatef(x, y, 0);
			glScalef(gX/1024*((double)scale/100),gY/786*((double)scale/100),1);
				glRotatef(rotate,0,0,1);
					for (int i=0; i<length; i++)
						glutStrokeCharacter(font, string[i]);
	glPopMatrix();
}

// Outputs a number to the screen at the specified location
void number_output(double x, double y, double num) {
	void *font = GLUT_BITMAP_9_BY_15;
	string temp;
	stringstream out;
	out << num;
	temp = out.str();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int)temp.length();
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, temp[i]);
	glDisable(GL_BLEND);
}

// Outputs a number in 'stroke' text format
void stroke_number(double x, double y, int scale, int rotate, double num) {
	void *font = GLUT_STROKE_ROMAN;
	string temp;
	stringstream out;
	out << num;
	temp = out.str();
	
	int length = (int)temp.size();
	glPushMatrix();
		glTranslatef(x, y, 0);
			glScalef(gX/1024*((double)scale/100),gY/786*((double)scale/100),1);
				glRotatef(rotate,0,0,1);
					for (int i=0; i<length; i++)
						glutStrokeCharacter(font, temp[i]);
	glPopMatrix();
}

// Return a random number between a low and a high
int random(int low, int high) {
	return rand() % (high-low+1) + low;
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h) {
	// Reset the global variables to the new width and height.
	gX = w;
	gY = h;
	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);
	// Redraw the screen
	glutPostRedisplay();
}

void Set2DView() {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the world coordinates.
	glOrtho(0, gX, 0, gY, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Set3DView() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (double)gX / (double)gY;
	gluPerspective(gZoom, aspectRatio, gNear, gFar);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(EYE[0],EYE[1],EYE[2],  AT[0],AT[1],AT[2],  UP[0],UP[1],UP[2]);
}

double GetFPS() {
	static clock_t startTime = clock();
	
	double fps = clock() - startTime;
	startTime  = clock();
	return fps;
}

// Returns the number of frames used devided by the time passed
double GetFramesPerSecond() {
	static int frames = 0;
	static clock_t startTime = clock();
	
	frames++;
	clock_t currentTime = clock();
	double elapsedTime = (double)(currentTime - startTime)/((double)CLOCKS_PER_SEC);
	return frames/elapsedTime;
}
