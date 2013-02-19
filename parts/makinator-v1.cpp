void DrawMakinatorV1(double mSize, double mX, double mY, double mZ, bool trans, bool wide) {
	// 1 and 2 inches
	double one = 25;
	double two = 2 * one;
	// Function pointer for different box types
	void (*box)(double, double, double) = trans ? DrawWireBox : DrawSolidBox;
	// Length, Width, and Height of the different tubes
	double len = mSize + one + two;
	color(trans ? black : gray25);
	glPushMatrix(); // X Axis 2x2 bars
		glRotated(wide ? 90 : 0, 0,0,1);
			glTranslated(0, len/2, mSize/2-one);
				box(mSize-one, two, two);
				glTranslated(0, -len, 0);
					box(mSize-one, two, two);
					glTranslated(0, 0, -mSize);
				box(mSize-one, two, two);
				glTranslated(0, len, 0);
			box(mSize-one, two, two);
	glPopMatrix();
	if (!trans) color(gray50);
	double wid = mSize + one;
	glPushMatrix(); // Z Axis Legs
		glRotated(wide ? 90 : 0, 0,0,1);
			glTranslated(wid/2, -len/2, -mSize/2-one);
				box(two, two, mSize+two);
				glTranslated(-wid, 0, 0);
					box(two, two, mSize+two);
					glTranslated(0, len, 0);
				box(two, two, mSize+two);
				glTranslated(wid, 0, 0);
			box(two, two, mSize+two);
	glPopMatrix();
	if (!trans) color(gray75);
	len = mSize + two;
	glPushMatrix(); // Y Axis 1x2 bars
		glRotated(wide ? 90 : 0, 0,0,1);
			glTranslated(len/2, 0, mSize/2-one);
				box(one, wid, two); // +X Upper
				glTranslated(-len, 0, 0);
					box(one, wid, two); // -X Upper
					glTranslated(0, 0, -mSize);
				box(one, wid, two); // -X Lower
				glTranslated(len, 0, 0);
			box(one, wid, two); // +X Lower
	glPopMatrix();
	if (!trans) color(ivery);
	len = wide ? mSize+140: mSize+90;
	glPushMatrix(); // Y Axis Wheel Carriage
		glTranslated(-len/2+15, mY, mSize/2+10);
			DrawSolidBox(30, one, 4);
			glTranslated(-15, 0, -55);
				box(4, 120, 90);
				glTranslated(len-15, 0, 55);
					DrawSolidBox(30, one, 4);
					glTranslated(15, 0, -55);
						box(4, 120, 90);
	glPopMatrix();
	color(lightRed);
	glPushMatrix(); // Z Axis Plate (Print Bed)
		glTranslated(0, 0, mZ+20);
			DrawSolidBox(mSize+20, mSize+20, 4);
	glPopMatrix();
	color(gray25);
	glPushMatrix(); // Z Axis Platform
		glRotated(wide ? 90 : 0, 0,0,1);
			glTranslated(0, 0, mZ);
				DrawSolidBox(mSize+20, 4, 20); // X
				glTranslated(0, mSize/2+8, 0);
					DrawSolidBox(mSize+20, 4, 20); // +X
					glTranslated(0, -mSize-16, 0);
						DrawSolidBox(mSize+20, 4, 20); // -X
						glTranslated(0, mSize/2+8, 0);
							DrawSolidBox(4, mSize+20, 20); // Y
							glTranslated(-mSize/2-8, 0, 0);
								DrawSolidBox(4, mSize+70, 20); // -Y
								glTranslated(mSize+16, 0, 0);
									DrawSolidBox(4, mSize+70, 20); // +Y
	glPopMatrix();
	color(black);
	wid = wide ? mSize/2+58 : mSize/2+33;
	glPushMatrix(); // Y Axis V Wheels Right
		glTranslated(wid, mY, mSize/2-37);
			glRotated(90, 0,1,0);
				DrawSolidCylinder(8, 12, 15, 0); // Lower
				glTranslated(-74, -51, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Near
					glTranslated(0, 102, 0);
						DrawSolidCylinder(8, 12, 15, 0); // Far
	glPopMatrix();
	glPushMatrix(); // Y Axis V Wheels Left
		glTranslated(-wid, mY, mSize/2-37);
			glRotated(-90, 0,1,0);
				DrawSolidCylinder(8, 12, 15, 0); // Lower
				glTranslated(74, -51, 0);
					DrawSolidCylinder(8, 12, 15, 0); // Near
					glTranslated(0, 102, 0);
						DrawSolidCylinder(8, 12, 15, 0); // Far
	glPopMatrix();
	glPushMatrix(); // Print Area Outline
		glTranslated(0, 0, mZ + one);
			DrawRectangle(-mSize/2,-mSize/2, mSize/2,mSize/2, 1);
	glPopMatrix();
	wid = wide ? mSize/2+72 : mSize/2+47;
	glPushMatrix(); // X Motor
		glTranslated(wid, mY+30, mSize/2+37);
			glRotated(90, 0,1,0);
				glRotated(45, 0,0,1);
					DrawMotor(true);
	glPopMatrix();
	color(darkGreen);
	wid = wide ? 80: 30;
	glPushMatrix(); // X Carriage
		glTranslated(mX, mY+30, mSize/2+37);
			glTranslated(-wid/2, 21, 0);
				DrawLM10UU(); // Left
				glTranslated(wid, 0, 0);
					DrawLM10UU(); // Right
			glTranslated(-wid/2, -21, 0);
			DrawLM10UU(); // Center
			glTranslated(-wid/2, -60, 0);
				DrawLM10UU(); // Left
				glTranslated(wid, 0, 0);
					DrawLM10UU(); // Right
			glTranslated(-wid, -21, 0);
				DrawLM10UU(); // Left
				glTranslated(wid, 0, 0);
					DrawLM10UU(); // Right
	glPopMatrix();
	color(silver);
	len = wide ? mSize+140: mSize+90;
	glPushMatrix(); // X Axis Rods
		glTranslated(0, mY, mSize/2+37);
			glRotated(90, 0,1,0);
				glTranslated(0, -51, -len/2);
					DrawSolidCylinder(len, 5, 10, 1); // --Y
					glTranslated(0, 21, 0);
						DrawSolidCylinder(len, 5, 10, 1); // -Y
						glTranslated(0, 60, 0);
						color(yellow);
							DrawSolidCylinder(len, 5, 10, 1); // +Y
							glTranslated(0, 21, 0);
								color(silver);
								DrawSolidCylinder(len, 5, 10, 1); // ++Y
	glPopMatrix();
	color(yellow);
	if (trans) {
		len = wide ? mSize+two : mSize;
		wid = wide ? mSize : mSize+two+one;
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
		len = wide ? mSize+two: mSize+120;
		wid = wide ? mSize+one+two: mSize+two;
		glPushMatrix(); // Y Screws
			glRotated(90, 1,0,0);
				glTranslated(-wid/2, mSize/2, -len/2);
					DrawSolidCylinder(len, 5, 10, 1);
					glTranslated(wid, 0, 0);
						DrawSolidCylinder(len, 5, 10, 1);
		glPopMatrix();
		if (!wide) {
			color(lightBlue);
			glPushMatrix(); // Y Screw Gears
				glRotated(90, 1,0,0);
					glTranslated(-wid/2, mSize/2, len/2-10);
						DrawSolidCylinder(10, 10, 15, 0);
						glTranslated(wid, 0, 0);
							DrawSolidCylinder(10, 10, 15, 0);
			glPopMatrix();
			wid -= 44 + 20;
			glPushMatrix(); // Y Idler Gears
				glRotated(90, 1,0,0);
					glTranslated(-wid/2, mSize/2, len/2-10);
						DrawSolidCylinder(10, 22, 20, 0);
						glTranslated(wid, 0, 0);
							DrawSolidCylinder(10, 22, 20, 0);
			glPopMatrix();
			glPushMatrix(); // Y Drive Gears
			glPopMatrix();
		}
		glPushMatrix(); // Y Motors
		len = mSize-60;
		if (wide) {
			wid = wide ? mSize+one+two: mSize+two;
			glRotated(90, 1,0,0);
				glTranslated(-wid/2, mSize/2, mSize/2+15);
					DrawMotor(true);
					glTranslated(wid, 0, 0);
						DrawMotor(true);
		} else {
			glTranslated(0, -mSize/2-37.5, mSize/2);
				glRotated(90, 0,1,0);
					glTranslated(0, 0, -len/2);
						DrawMotor(true);
						glTranslated(0, 0, len);
							glRotated(180, 0,1,0);
								DrawMotor(true);
		}
		glPopMatrix();
		glPushMatrix(); // Z Motors
		if (wide) {
			glRotated(90, 0,0,1);
				glTranslated(-len/2, mSize/2+37.5, -mSize/2+22);
					glRotated(90, 0,1,0);
						DrawMotor(true); // Q4
						glTranslated(0, -mSize-one-two, 0);
							DrawMotor(true); // Q3
							glTranslated(0, 0, len);
						glRotated(180, 0,1,0);
					DrawMotor(true); // Q2
					glTranslated(0, mSize+one+two ,0);
				DrawMotor(true); // Q1
		} else {
			glRotated(180, 0,1,0);
				glTranslated(mSize/2, -mSize/2-one*1.5, mSize/2+5);
					DrawMotor(true); // Q4
					glTranslated(-mSize, 0, 0);
						DrawMotor(true); // Q3
						glTranslated(0, mSize+one+two, 0);
					DrawMotor(true); // Q2
					glTranslated(mSize, 0, 0);
				DrawMotor(true); // Q1
		}
		glPopMatrix();
	}
	/*
	glPushMatrix(); //
	glPopMatrix();
	*/
}
