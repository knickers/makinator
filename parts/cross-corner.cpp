void DrawCrossCorner(double mSize, double mR, double mX, double mY, double mZ) {
	glPushMatrix();
		glTranslated(mSize-mR*5,mSize-mR*5,mR*1.25);
			DrawMotor(false);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray75);
	glRotated(-90, 1,0,0);
		glPushMatrix(); // Y axis rod supports
			glRotated(90, 0,1,0);
			glTranslated(mSize,0,-mSize+mR);
				DrawSolidCylinder(mSize*2-mR*2, mR, 10, 1);
				glTranslated(-mSize*2,0,0);
					DrawSolidCylinder(mSize*2-mR*2, mR, 10, 1);
		glPopMatrix();
		glPushMatrix(); // Y axis rods
			glTranslated(mSize,0,-mSize+mR);
				DrawSolidCylinder(mSize*2-mR*2, mR, 10, 1);
				glTranslated(-mSize*2,0,0);
					DrawSolidCylinder(mSize*2-mR*2, mR, 10, 1);
		glPopMatrix();
		glPushMatrix();
			glTranslated(0,0,mY); // Y axis motion
				glPushMatrix(); // X axis rods
					glRotated(90, 0,1,0);
						glTranslated(mR*6,0,-mSize+mR*2);
							DrawSolidCylinder(mSize*2-mR*4, mR, 10, 1);
							glTranslated(-mR*12,0,0);
								DrawSolidCylinder(mSize*2-mR*4, mR, 10, 1);
				glPopMatrix();
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
				glPushMatrix(); // Y axis sliders
					glTranslated(-mSize,0,0);
						DrawSlider(mR);
						glTranslated(mSize*2,0,0);
							glRotated(180, 0,1,0);
								DrawSlider(mR);
				glPopMatrix();
				glPushMatrix(); // X axis sliders
					glTranslated(mX,0,0); // X axis motion
						glRotated(90, 0,1,0);
							DrawTrolley(mR);
				glPopMatrix();
		glPopMatrix();
	glRotated(90, 1,0,0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
	glPushMatrix();
		glRotated(90, 0,0,1);
			DrawCornerMount(mSize, mR);
			glRotated(90, 0,0,1);
				DrawCornerMount(mSize, mR);
				glRotated(90, 0,0,1);
					DrawCornerMount(mSize, mR);
					glRotated(90, 0,0,1);
						DrawCornerMount(mSize, mR);
	glPopMatrix();
}
