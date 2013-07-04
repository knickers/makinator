void DrawMakinatorV2(double mSize, double mX, double mY, double mZ, bool trans){
	// Function pointer for different box types
	void (*box)(double, double, double) = trans ? DrawWireBox : DrawSolidBox;
	// Length, Width, and Height of the different tubes
	double len = mSize + TWO;
	color(trans ? black : gray25);
	glPushMatrix(); // X Axis 2x2 bars
		glTranslated(0, len/2, mSize/2-ONE);
			box(mSize-TWO, TWO, TWO);
			glTranslated(0, -len, 0);
				box(mSize-TWO, TWO, TWO);
				glTranslated(0, 0, -mSize);
			box(mSize-TWO, TWO, TWO);
			glTranslated(0, len, 0);
		box(mSize-TWO, TWO, TWO);
	glPopMatrix();
	if (!trans) color(gray50);
	double wid = len - ONE;
	glPushMatrix(); // Z Axis Legs 3x2 bars
		glTranslated(wid/2, -len/2, -len/2);
			box(TRE, TWO, len);
			glTranslated(-wid, 0, 0);
				box(TRE, TWO, len);
				glTranslated(0, len, 0);
			box(TRE, TWO, len);
			glTranslated(wid, 0, 0);
		box(TRE, TWO, len);
	glPopMatrix();
	if (!trans) color(gray75);
	wid -= ONE;
	glPushMatrix(); // Y Axis 2x2 bars
		glTranslated(len/2, 0, mSize/2-ONE);
			box(TWO, wid, TWO); // +X Upper
			glTranslated(-len, 0, 0);
				box(TWO, wid, TWO); // -X Upper
				glTranslated(0, 0, -mSize);
			box(TWO, wid, TWO); // -X Lower
			glTranslated(len, 0, 0);
		box(TWO, wid, TWO); // +X Lower
	glPopMatrix();
	if (!trans) color(ivery);
	len += TWO + 15;
	glPushMatrix(); // Y Axis Wheel Carriage
		glTranslated(-len/2+15, mY, mSize/2+10);
			DrawSolidBox(30, ONE, 4);
			glTranslated(-15, 0, -55);
				box(4, 120, 90);
				glTranslated(len-15, 0, 55);
					DrawSolidBox(30, ONE, 4);
					glTranslated(15, 0, -55);
						box(4, 120, 90);
	glPopMatrix();
	color(lightRed);
	glPushMatrix(); // Z Axis Plate (Print Bed)
		glTranslated(0, 0, mZ + ONE- 5);
			DrawSolidBox(mSize-2, mSize-2, 4);
	glPopMatrix();
	color(gray25);
	glPushMatrix(); // Z Axis Platform
		glTranslated(0, 0, mZ);
			DrawSolidBox(mSize, 4, 20); // Y
			glTranslated(0, mSize/2-2, 0);
				DrawSolidBox(mSize, 4, 20); // +Y
				glTranslated(0, -mSize+4, 0);
					DrawSolidBox(mSize, 4, 20); // -Y
					glTranslated(0, mSize/2-2, 0);
						DrawSolidBox(4, mSize, 20); // X
						glTranslated(-mSize/2+2, 0, 0);
							DrawSolidBox(4, mSize+TWO, 20); // -X
							glTranslated(mSize-4, 0, 0);
								DrawSolidBox(4, mSize+TWO, 20); // +X
	glPopMatrix();
	color(black);
	wid = mSize + 2*TWO;
	glPushMatrix(); // Y Axis V Wheels
		glTranslated(-wid/2, mY, mSize/2-ONE-12);
			v_wheels(2*TWO, 74); // Left
			glTranslated(wid, 0, 0);
				v_wheels(2*TWO, 74); // Right
	glPopMatrix();
	glPushMatrix(); // X Motor
		glTranslated(wid/2+14, mY+30, mSize/2+37);
			glRotated(90, 0,1,0);
				glRotated(45, 0,0,1);
					DrawMotor(true);
	glPopMatrix();
	color(darkGreen);
	wid = TWO;
	glPushMatrix(); // X Carriage
		glTranslated(mX-wid/2, mY+TWO, mSize/2+37); // ++Y
			DrawLM10UU(); // Left
			glTranslated(wid, 0, 0);
				DrawLM10UU(); // Right
		glTranslated(-wid/2, -ONE, 0); // +Y
		DrawLM10UU(); // Center
		glTranslated(-wid/2, -TWO, 0); // -Y
			DrawLM10UU(); // Left
			glTranslated(wid, 0, 0);
				DrawLM10UU(); // Right
		glTranslated(-wid, -ONE, 0); // --Y
			DrawLM10UU(); // Left
			glTranslated(wid, 0, 0);
				DrawLM10UU(); // Right
	glPopMatrix();
	color(blue);
	glPushMatrix(); // Extruder Position
		glTranslated(mX, mY, mSize/2 + ONE + 10);
			DrawSolidCylinder(ONE, 4, 8, 0);
			DrawTaperCylinder(-10, 4, 0, 8, 0);
	glPopMatrix();
	color(silver);
	len = mSize + 4*ONE + 15;
	glPushMatrix(); // X Axis Rods
		glTranslated(0, mY-ONE, mSize/2+37);
			glRotated(90, 0,1,0);
				glTranslated(0, -ONE, -len/2);
					DrawSolidCylinder(len, 5, 10, 1); // --Y
					glTranslated(0, ONE, 0);
						DrawSolidCylinder(len, 5, 10, 1); // -Y
						glTranslated(0, TWO, 0);
						color(yellow);
							DrawSolidCylinder(len, 5, 10, 1); // +Y
							glTranslated(0, ONE, 0);
								color(silver);
								DrawSolidCylinder(len, 5, 10, 1); // ++Y
	glPopMatrix();
	color(yellow);
	if (trans) {
		len = mSize - ONE;
		wid = mSize + TWO;
		glPushMatrix(); // Z Screws
			glTranslated(len/2, -wid/2, -mSize/2);
				DrawSolidCylinder(mSize+20, 5, 10, 1); // Q4
				glTranslated(-len, 0, 0);
					DrawSolidCylinder(mSize+20, 5, 10, 1); // Q3
					glTranslated(0, wid, 0);
				DrawSolidCylinder(mSize+20, 5, 10, 1); // Q2
				glTranslated(len, 0, 0);
			DrawSolidCylinder(mSize+20, 5, 10, 1); // Q1
		glPopMatrix();
		len += 4*ONE;
		glPushMatrix(); // Y Screws
			glRotated(90, 1,0,0);
				glTranslated(-wid/2, mSize/2, -len/2-10);
					DrawSolidCylinder(len, 5, 10, 1);
					glTranslated(wid, 0, 0);
						DrawSolidCylinder(len, 5, 10, 1);
		glPopMatrix();
		glPushMatrix(); // Y Motors
		len = mSize + TWO;
			glTranslated(0, -mSize/2-ONE, mSize/2);
				glRotated(90, 1,0,0);
					glTranslated(-len/2, 0, 0);
						DrawMotor(true);
						glTranslated(len, 0, 0);
								DrawMotor(true);
		glPopMatrix();
		glPushMatrix(); // Z Motors
			glRotated(180, 0,1,0);
				glTranslated(mSize/2-ONE/2, -mSize/2-ONE, mSize/2+5);
					DrawMotor(true); // Q4
					glTranslated(-mSize+ONE, 0, 0);
						DrawMotor(true); // Q3
						glTranslated(0, mSize+TWO, 0);
					DrawMotor(true); // Q2
					glTranslated(mSize-ONE, 0, 0);
				DrawMotor(true); // Q1
		glPopMatrix();
	}
	/*
	glPushMatrix(); //
	glPopMatrix();
	*/
}
