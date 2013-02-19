void DrawOrdBot(double mSize, double mX, double mY, double mZ) {
	color(gray50);
	glPushMatrix(); // X Axis Makerslide
		glTranslated(0, 35, mZ+25);
			DrawSolidBox(mSize+90, 20, 40);
	glPopMatrix();
	glPushMatrix(); // Y Axis Makerslide
		glTranslated(0, 0, -mSize/2-30);
			DrawSolidBox(40, mSize+40, 20);
	glPopMatrix();
	glPushMatrix(); // Z Axis Makerslides
		glTranslated(-mSize/2-25, 62, -mSize/2-35);
			DrawSolidBox(40, 20, mSize+105);
			glTranslated(mSize+50, 0, 0);
				DrawSolidBox(40, 20, mSize+105);
	glPopMatrix();
	glPushMatrix(); // Top and Bottom of Z Axis
		glTranslated(0, 62, mSize/2+60+10);
			DrawSolidBox(mSize+90, 20, 20);
			glTranslated(0, 0, -mSize-120);
				DrawSolidBox(mSize+90, 20, 20);
	glPopMatrix();
	color(lightRed);
	glPushMatrix(); // Print Bed
		glTranslated(0, mY, -mSize/2-4);
			DrawSolidBox(mSize+5, mSize+5, 4);
	glPopMatrix();
	color(black);
	glPushMatrix(); // Print Area Outline
		glTranslated(0, mY, -mSize/2+0.5);
			DrawRectangle(-mSize/2,-mSize/2, mSize/2,mSize/2, 1);
	glPopMatrix();
	glPushMatrix(); // X Axis V-Wheels
		glTranslated(mX, 31, mZ+45);
			glRotated(90, 1,0,0);
				glTranslated(12.5, -32, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Q4
					glTranslated(-25, 0, 0);
						DrawSolidCylinder(8, 12, 15, 0); // Q3
						glTranslated(0, 64, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Q2
					glTranslated(25, 0, 0);
				DrawSolidCylinder(8, 12, 15, 0); // Q1
	glPopMatrix();
	glPushMatrix(); // Y Axis V-Wheels
		glTranslated(32, mY-12.5, -mSize/2-15);
			DrawSolidCylinder(8, 12, 15, 0); // Q4
			glTranslated(-64, 0, 0);
				DrawSolidCylinder(8, 12, 15, 0); // Q3
				glTranslated(0, 25, 0);
			DrawSolidCylinder(8, 12, 15, 0); // Q2
			glTranslated(64, 0, 0);
		DrawSolidCylinder(8, 12, 15, 0); // Q1
	glPopMatrix();
	glPushMatrix(); // Z Axis V-Wheels
		glTranslated(0, 57, mZ+40);
			glRotated(90, 1,0,0);
				glTranslated(mSize/2-7, -27, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Q4
					glTranslated(-mSize+14, 0, 0);
						DrawSolidCylinder(8, 12, 15, 0); // Q3
						glTranslated(0, 40, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Q2
					glTranslated(mSize-14, 0, 0);
				DrawSolidCylinder(8, 12, 15, 0); // Q1
	glPopMatrix();
	color(ivery);
	glPushMatrix(); // Z Axis Wheel Plates
		glTranslated(-mSize/2-25, 47, mZ+5);
			DrawSolidBox(80, 4, 60);
			glTranslated(mSize+50, 0, 0);
				DrawSolidBox(80, 4, 60);
	glPopMatrix();
	glPushMatrix(); // Extruder Platform
		glTranslated(mX, 20, mZ+5);
			DrawSolidBox(50, 4, 80);
			glTranslated(0, -20, 0);
				DrawSolidBox(50, 40, 4);
	glPopMatrix();
	color(red);
	glPushMatrix(); //
	glPopMatrix();
	glPushMatrix(); //
	glPopMatrix();
}
