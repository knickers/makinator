#include <cmath>
using namespace std;
#include "printer.h"
#include "colors.h"
#include "shapes.h"
#include "parts/parts.cpp"
#include "parts/cross-corner.cpp"
#include "parts/joint-corner.cpp"
#include "parts/makinator-v0.cpp"
#include "parts/makinator-v1.cpp"
#include "parts/makinator-v2.cpp"
#include "parts/ordbot.cpp"

Printer::Printer() {
	mR = 4; // Pipe radius in millimeters
	mType = 5;
	mSize = 100; // Print Area Cube in millimeters
	mPause = 0;
	Set(0, 0, 0);
	mTitles[0] = "Cross Corners";
	mTitles[1] = "Joint Corners";
	mTitles[2] = "Makinator v0";
	mTitles[3] = "Makinator v1";
	mTitles[4] = "Makinator v2";
	mTitles[5] = "Ord Bot";
	mOption[0] = mOption[1] = mOption[2] = false;
	mOptions[0] = "- none -";
	mOptions[1] = "- none -";
	mOptions[2] = "a) Toggle Table b) Toggle Leg Width";
	mOptions[3] = "a) Toggle Table b) Toggle Transparency c) Toggle Direction";
	mOptions[4] = "a) Toggle Table b) Toggle Transparency";
	mOptions[5] = "- none -";
}

Printer::~Printer() {
}

void Printer::DrawCrossMount() {
	double overlap = mR*1.5;
	glPushMatrix(); // X axis
		glRotated(90, 0,1,0);
			glTranslated(-mR*1.5,0,-overlap);
				DrawSolidCylinder(mR*10, mR*1.5, 15, 0);
	glPopMatrix();
	glPushMatrix(); // Y axis
		glRotated(-90, 1,0,0);
			glTranslated(0,mR*1.5,-overlap);
				DrawSolidCylinder(mR*10, mR*1.5, 15, 0);
	glPopMatrix();
	DrawSolidCylinder(-mR*10, mR*1.5, 15, 0); // Z axis
	
	glTranslated( mR*3.5, mR*1.25, 0);
		DrawSolidBox(mR*10, mR/2, mR*8); // Upper (x) Motor Support
	glTranslated(-mR*3.5+mR*1.25, -mR*1.25+mR*3.5, 0-mR*8);
		DrawSolidBox(mR/2, mR*10, mR*8); // Lower (y) Motor Support
	glTranslated(-mR*1.25+mR*3.5, -mR*3.5+mR*3.5, mR*8-mR/2);
		DrawSolidBox(mR*10, mR*10, mR); // Vertical (z) Motor Support
	glTranslated(-mR*3.5,-mR*3.5, mR/2);
	glRotated(-90, 1,0,0); // Vertical Tube Support
		DrawExtrudeTriangle(mR*1.5,mR/2, mR*1.5,mR*8, mR*8.5,mR/2, mR/2);
	glRotated(90, 1,0,0);
}

void Printer::DrawCornerAssembly(int t) {
	if (t == 1) {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray50);
		glPushMatrix(); // Z axis
			glTranslated(mR*3, mR*3, mR*1.5);
				DrawMotor(false);
		glPopMatrix();
		glPushMatrix(); // Y axis
			glTranslated(mR*7.5, mR*1.5, -mR*3);
				glRotated(-90, 1,0,0);
					DrawMotor(false);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
		DrawJointMount(mR);
	} else if (t == 2) {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
		DrawCrossMount();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray50);
		if (1) {
			glPushMatrix(); // Upper Motor X axis
				glTranslated(mR*4, mR*1.5, mR*4.5);
					glRotated(-90, 1,0,0);
					DrawMotor(false);
			glPopMatrix();
			glPushMatrix(); // Lower Motor Y axis
				glTranslated(mR*1.5, mR*4,-mR*4.5);
					glRotated(90, 0,1,0);
					DrawMotor(false);
			glPopMatrix();
		} else {
			glPushMatrix(); // Vertical Motor Z axis
				glTranslated(mR*5, mR*5, mR/2);
					DrawMotor(false);
			glPopMatrix();
		}
	}
}

void Printer::Draw() {
	switch (mType) {
	case 1: // Cross Corner
		DrawCrossCorner(mSize, mR, mX, mY, mZ);
		break;
	case 2: // Joint Corner
		DrawJointCorner(mSize, mR, mX, mY, mZ);
		break;
	case 3: // Makinator v0
		DrawMakinatorV0(mSize, mX, mY, mZ, mOption[1]);
		break;
	case 4: // Makinator v1
		DrawMakinatorV1(mSize, mX, mY, mZ, mOption[1], mOption[2]);
		break;
	case 5: // Makinator v2
		DrawMakinatorV2(mSize, mX, mY, mZ, mOption[1]);
		break;
	case 6: // Ord Bot
		DrawOrdBot(mSize, mX, mY, mZ);
		break;
	dafault:
		break;
	}
	if (mOption[0]) {
		color(brown);
		glTranslated(0, 0, -mSize/2 - 500);
			DrawTable(1280, 760, 475);
		glTranslated(0, 0, mSize/2 + 500);
	}
}

void Printer::InitDisplayLists() {
/*
	glNewList(MOTOR, GL_COMPILE);
		DrawMotor(false);
	glEndList();
*/
}

void Printer::Pause(bool p) {
	mPause = p;
}

bool Printer::Pause() {
	return mPause;
}

double Printer::zeroToOne(double n) {
	return n < 0 ? 0 : (n > 1 ? 1 : n);
}

void Printer::Set(double x, double y, double z) {
	SetX(x);
	SetY(y);
	SetZ(z);
}
void Printer::SetX(double x) {
	mX = zeroToOne(x)*mSize - mSize/2;
}
void Printer::SetY(double y) {
	mY = zeroToOne(y)*mSize - mSize/2;
}
void Printer::SetZ(double z) {
	mZ = zeroToOne(z)*mSize - mSize/2;
}

void Printer::SetType(unsigned type) {
	if (type < 7) {
		mType = type;
		mOption[0] = mOption[1] = false;
	}
}

void Printer::SetSize(double size) {
	mSize = size;
}
double Printer::GetSize() {
	return mSize;
}

string Printer::Title() {
	return mTitles[mType-1];
}

string Printer::Options() {
	return mOptions[mType-1];
}
void Printer::Option(char o) {
	if (o == 'a') {
		mOption[0] = !mOption[0];
	} else if (o == 'b') {
		mOption[1] = !mOption[1];
	} else if (o == 'c') {
		mOption[2] = !mOption[2];
	}
}
