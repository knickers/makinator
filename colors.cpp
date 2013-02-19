#include "colors.h"
#include <GL/glut.h>

float silver[]      = { .7, .8, .8,  1};
float ivery[]		= { .8, .9, .5,  1};
float black[]		= {  0,  0,  0,  1};
float white[]		= {  1,  1,  1,  1};
float red[]			= {  1,  0,  0,  1};
float darkRed[]		= { .5,  0,  0,  1};
float lightRed[]	= {  1, .2, .2,  1};
float green[]		= {  0,.75,  0,  1};
float darkGreen[]	= {  0, .5,  0,  1};
float lightGreen[]	= { .2,.75, .2,  1};
float blue[]		= {  0,  0,  1,  1};
float lightBlue[]	= { .1, .5, .8,  1};
float navyBlue[]	= { .2, .2, .7,  1};
float yellow[]		= {  1,  1,  0,  1};
float brown[]		= { .3, .2, .1,  1};
float gray[]		= { .4, .4, .3,  1};
float gray10[]		= { .1, .1, .1,  1};
float gray25[]		= {.25,.25,.25,  1};
float gray50[]		= { .5, .5, .5,  1};
float gray75[]		= {.75,.75,.75,  1};
float lightGray[]	= { .6, .6, .5,  1};
float darkGray[]	= { .3, .3, .2,  1};
float clear[]		= {  1,  1,  1,  0};
float transBlue[]	= {  0,  0,  1,.35};
float transNavy[]	= {  0,  0, .5, .5};
float transRed[]	= {  1,  0,  0,.75};
float transYellow[]	= {  1,  1,  0, .5};
float transOrange[]	= {  1, .5,.25, .5};

void color(float* c) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c);
}

void color(float r, float g, float b, float a) {
//	glMaterialf(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, r,g,b,a);
}
