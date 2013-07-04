void DrawSidePanel(double mSize, bool trans, void (*box)(double, double, double)) {
	glPushMatrix(); // Top and bottom bars
		glTranslated(0, -ONE/2, -mSize/2-ONE);
			box(4, mSize+TRE, mSize-TWO); // -Z bar
			glTranslated(0, 0, mSize-ONE);
				box(4, mSize+TRE, TWO); // +Z bar
	glPopMatrix();
	glPushMatrix(); // Front and back bars
		glTranslated(0, -mSize/2-TRE/2, mSize/2-TRE);
			box(4, ONE, ONE); // -Y
			glTranslated(0, mSize+TWO, 0);
				box(4, ONE, ONE); // +Y
	glPopMatrix();
};

void DrawMakinatorMini(double mSize, double mX, double mY, double mZ, bool trans) {
	// Function pointer for different box types
	void (*box)(double, double, double) = trans ? DrawWireBox : DrawSolidBox;
	/*
	color(yellow);
	glPushMatrix(); // Mock Print Area
		glTranslated(0, 0, -mSize/2);
			DrawSolidBox(mSize, mSize, mSize);
	glPopMatrix();
	*/
	double wid = mSize + ONE + HLF;
	
	color(black);
	glPushMatrix(); // Y Axis V Wheels
		glTranslated(-wid/2, mY-HLF, mSize/2-TWO-HLF);
			v_wheels(TWO, TRE); // Left
			glTranslated(wid, 0, 0);
				v_wheels(TWO, TRE); // Right
	glPopMatrix();
	
	if (!trans) color(gray50);
	glPushMatrix(); // Left and Right Side Panels
		glTranslated(-wid/2, 0, 0);
			DrawSidePanel(mSize, trans, box); // -X
			glTranslated(wid, 0, 0);
				DrawSidePanel(mSize, trans, box); // +X
	glPopMatrix();
	
	color(darkGreen);
	glPushMatrix(); // X Carriage
		glTranslated(mX, mY-TRE/2, mSize/2+HLF); // +Y
			DrawLM10UU(); // Center
			glTranslated(0, TWO, 0); // -Y
				DrawLM10UU(); // Left
	glPopMatrix();
	
	color(blue);
	glPushMatrix(); // Extruder Position
		glTranslated(mX, mY-HLF/6, mSize/2+HLF);
			DrawSolidCylinder(ONE, 4, 8, 0);
			DrawTaperCylinder(-10, 4, 0, 8, 0);
	glPopMatrix();
	
	wid += HLF;
	color(silver);
	glPushMatrix(); // X Axis Rods
		glTranslated(-wid/2, mY-TRE/2, mSize/2+HLF);
			glRotated(90, 0,1,0);
				DrawSolidCylinder(wid, 3, 10, !trans); // -Y
				glTranslated(0, TWO, 0);
					DrawSolidCylinder(wid, 3, 10, !trans); // +Y
	glPopMatrix();
	
	glPushMatrix(); // Y axis wheel carriages
		glRotated(90, 0,1,0);
			glTranslated(-mSize/2+HLF-2, mY-HLF, -mSize/2-ONE-4);
				DrawSolidCylinder(4, TWO+HLF, ONE+HLF, 3, 0);
				glTranslated(0, 0, mSize+TWO+4);
					DrawSolidCylinder(4, TWO+HLF, ONE+HLF, 3, 0);
	glPopMatrix();
	
	color(lightRed);
	glPushMatrix(); // Z Axis Plate (Print Bed)
		glTranslated(0, 0, mZ);
			DrawSolidBox(mSize, mSize, 4);
	glPopMatrix();
	
	wid = mSize + ONE + HLF/2;
	glPushMatrix(); // X/Y Motors
		glTranslated(-wid/2, -mSize/2-ONE, mSize/2-ONE);
			glRotated(90, 0,1,0);
				DrawMotor(false);
				glTranslated(0, 0, wid);
					glRotated(180, 1,0,0);
						DrawMotor(false);
	glPopMatrix();
	/*
	glPushMatrix(); //
	glPopMatrix();
	*/
}
