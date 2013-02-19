void DrawJointMount(double mR) {
	glPushMatrix();
		glTranslated(0,0,mR);
			DrawSolidCylinder(-mR*10, mR*1.5, 15, 0); // Z axis
			glTranslated(0,0,-mR);
				glRotated(-90, 1,0,0);
					glTranslated(0,0,mR);
						DrawSolidCylinder(mR*10, mR*1.5, 15, 0); // Y axis
							glRotated(90, 0,1,0);
								glTranslated(mR,0,mR);
									DrawSolidCylinder(mR*10, mR*1.5, 15, 0);//X
	glPopMatrix();
	glTranslated(/*mR*4.75*/0,/*mR*4.75*/0,mR*2.5);
		glTranslated(0,0,-mR*1.25);
			DrawExtrudeTriangle(0,0, 0,mR*11, mR*11,0, mR/2);
		glTranslated(0,0,mR*1.25);
//		DrawSolidBox(mR*12.5, mR*12.5, mR/2); // x  y plane
	glTranslated(/*-mR*4.75+*/mR*1.25,/*-mR*4.75+*/mR*4.75,-mR*2.5-mR*9);
		DrawSolidBox(mR/2, mR*12.5, mR*10.5); // y -z plane
	glTranslated(-mR*1.25+mR*4.75,-mR*4.75+mR*1.25,mR*9-mR*9);
		DrawSolidBox(mR*12.5, mR/2, mR*10.5); // x -z plane
	glTranslated(-mR*4.75,-mR*1.25,mR*9);
}

void DrawEndCarriage(double mR) {
	glTranslated(0,0,-mR*1.5);
		DrawSolidBox(mR*3, mR*3, mR*6);
	glTranslated(0,0,mR*1.5);
}

void DrawJointCorner(double mSize, double mR, double mX, double mY, double mZ) {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray75);
	glPushMatrix(); // X rod
		glRotated(90, 1,0,0);
			glTranslated(mX, mR*3, -mSize/2-mR*2);
				DrawSolidCylinder(mSize+mR*4, mR, 10, 0);
	glPopMatrix();
	glPushMatrix(); // X supports
		glRotated(90, 0,1,0);
			glTranslated(0, -mSize/2, -mSize/2+mR);
				DrawSolidCylinder(mSize-mR*2, mR, 10, 1);
				glTranslated(0, mSize, 0);
					DrawSolidCylinder(mSize-mR*2, mR, 10, 1);
	glPopMatrix();
	glPushMatrix(); // Y rod
		glRotated(90, 0,1,0);
			glTranslated(mR*3, mY, -mSize/2-mR*2);
				DrawSolidCylinder(mSize+mR*4, mR, 10, 0);
	glPopMatrix();
	glPushMatrix(); // Y supports
		glRotated(90, 1,0,0);
			glTranslated(-mSize/2, 0, -mSize/2+mR);
				DrawSolidCylinder(mSize-mR*2, mR, 10, 1);
				glTranslated(mSize, 0, 0);
					DrawSolidCylinder(mSize-mR*2, mR, 10, 1);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glPushMatrix(); // X carriages
		glTranslated(mX,-mSize/2,0);
			DrawEndCarriage(mR);
			glTranslated(0,mSize,0);
				DrawEndCarriage(mR);
	glPopMatrix();
	glPushMatrix(); // Y carriages
		glTranslated(-mSize/2, mY, -mR*3);
			DrawEndCarriage(mR);
			glTranslated(mSize, 0, 0);
				DrawEndCarriage(mR);
	glPopMatrix();
	glPushMatrix(); // Center carriage
		glTranslated(mX, mY, -mR*5);
			DrawSolidBox(mR*4, mR*4, mR*10);
	glPopMatrix();
	for (int i=0; i<4; i++) { // Corner Mounts
		glPushMatrix();
			glRotated(i*90, 0,0,1);
				glTranslated(-mSize/2, -mSize/2, 0);
					DrawJointMount(mR);
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray50);
	glPushMatrix(); // X motor
		glTranslated(mSize/2-mR*5, -mSize/2+mR*1.5, -mR*3);
			glRotated(-90, 1,0,0);
				DrawMotor(false);
	glPopMatrix();
	glPushMatrix(); // Y motor
		glTranslated(-mSize/2+mR*1.5, mSize/2-mR*5, -mR*6);
			glRotated(90, 0,1,0);
				DrawMotor(false);
	glPopMatrix();
	glPushMatrix(); // Z motor q1
		glTranslated(mSize/2-mR*3, mSize/2-mR*3, mR*1.5);
			DrawMotor(false);
	glPopMatrix();
	glPushMatrix(); // Z motor q3
		glTranslated(-mSize/2+mR*3, -mSize/2+mR*3, mR*1.5);
			DrawMotor(false);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glPushMatrix(); // X pulleys +y
		glRotated(-90, 1,0,0);
			glTranslated(-mSize/2+mR*5, mR*3, mSize/2);
				DrawPulley(mR, mR);
				glTranslated(mSize-mR*10, 0, 0);
					DrawPulley(mR, mR);
	glPopMatrix();
	glPushMatrix(); // X pulleys -y
		glRotated(90, 1,0,0);
			glTranslated(-mSize/2+mR*5, -mR*3, mSize/2);
				DrawPulley(mR, mR);
				glTranslated(mSize-mR*10, 0, 0);
					DrawPulley(mR, mR);
	glPopMatrix();
	glPushMatrix(); // X belts upper
		glTranslated(0, -mSize/2, -mR*2);
			DrawSolidBox(mSize-mR*10, mR, mR/2);
			glTranslated(0, mSize, 0);
				DrawSolidBox(mSize-mR*10, mR, mR/2);
	glPopMatrix();
	glPushMatrix(); // X belts lower
		glTranslated(0, -mSize/2, -mR*4.5);
			DrawSolidBox(mSize-mR*10, mR, mR/2);
			glTranslated(0, mSize, 0);
				DrawSolidBox(mSize-mR*10, mR, mR/2);
	glPopMatrix();
	glPushMatrix(); // Y pulleys +x
		glRotated(90, 0,1,0);
			glTranslated(mR*6, -mSize/2+mR*5, mSize/2);
				DrawPulley(mR, mR);
				glTranslated(0, mSize-mR*10, 0);
					DrawPulley(mR, mR);
	glPopMatrix();
	glPushMatrix(); // Y pulleys -x
		glRotated(-90, 0,1,0);
			glTranslated(-mR*6, -mSize/2+mR*5, mSize/2);
				DrawPulley(mR, mR);
				glTranslated(0, mSize-mR*10, 0);
					DrawPulley(mR, mR);
	glPopMatrix();
	glPushMatrix(); // Y belts upper
		glTranslated(-mSize/2, 0, -mR*5);
			DrawSolidBox(mR, mSize-mR*10, mR/2);
			glTranslated(mSize, 0, 0);
				DrawSolidBox(mR, mSize-mR*10, mR/2);
	glPopMatrix();
	glPushMatrix(); // Y belts lower
		glTranslated(-mSize/2, 0, -mR*7.5);
			DrawSolidBox(mR, mSize-mR*10, mR/2);
			glTranslated(mSize, 0, 0);
				DrawSolidBox(mR, mSize-mR*10, mR/2);
	glPopMatrix();
}
