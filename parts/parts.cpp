// inch values
double ONE = 25;
double HLF = ONE/2;
double TWO = 2 * ONE;
double TRE = 3 * ONE;
double FOR = 4 * ONE;

// Draw three wheels, one centered below the other two
void v_wheels(double width, double height) {
	glPushMatrix();
		glRotated(-90, 0,1,0);
			glTranslated(0, 0, -4);
				DrawSolidCylinder(8, 12, 16, 0); // Lower
				glTranslated(height, -width/2, 0);
					DrawSolidCylinder(8, 12, 16, 0); // Near
					glTranslated(0, width, 0);
						DrawSolidCylinder(8, 12, 16, 0); // Far
	glPopMatrix();
}

void DrawSeperatedBars(double x, double y, double z, double d, int axis, void (*box)(double, double, double)) {
	double dX = axis == 0 ? d : 0;
	double dY = axis == 1 ? d : 0;
	double dZ = axis == 2 ? d : 0;
	glPushMatrix();
		glTranslated(-dX/2, -dY/2, -dZ/2);
			box(x, y, z);
//			glTranslated(dX, dY, dZ);
//				box(x, y, z);
	glPopMatrix();
}

void DrawPulley(double h, double r) {
	glPushMatrix();
		glTranslated(0,0,-h/2-2);
			DrawSolidCylinder(2, r+2, 15, 0); // Bottom retainer
			glTranslated(0,0,2);
				DrawSolidCylinder(h, r, 10, 1); // Center
				glTranslated(0,0,h);
					DrawSolidCylinder(2, r+2, 15, 0); // Top retainer
	glPopMatrix();
}

void MotorShape(double w, double h) {
	glBegin(GL_POLYGON);
	glVertex2d(-w, h); // Upper Left
	glVertex2d(-h, w);
	glVertex2d( h, w); // Upper Right
	glVertex2d( w, h);
	glVertex2d( w,-h); // Lower Right
	glVertex2d( h,-w);
	glVertex2d(-h,-w); // Lower Left
	glVertex2d(-w,-h);
	glEnd();
}
void DrawMotor(bool half) {
	// Nema 17 motor
	/* Inches
	double w = 1.680 / 2; // Half the length of a side and height
	double h = 1.220 / 2; // Half the length between the mounting holes
	*/
	/* Millimeters */
	double w = 42.67 / 2; // Half the length of a side
	double h = 31.00 / 2; // Half the length between the mounting holes
	double l = half ? w : w*2; // Height of the motor
	
	double r = (w-h) / 2; // Radius for the beveled corners
	double d = dtor(45); // Diagonal angle
	// Floor Ceiling
	color(gray75);
	glPushMatrix();
		glNormal3d(0, 0, -1);
		MotorShape(w, h);
		glTranslated(0, 0, l);
			glNormal3d(0, 0, 1);
			MotorShape(w, h);
	glPopMatrix();
	// Output Shaft
	DrawSolidCylinder(-w/1.06675, w/8.534, 10, 0);
	color(gray10);
	// Bearing Bevel
	DrawSolidCylinder(-w/10.6675, w/1.939, 15, 0);
	// Walls
	glNormal3d(0,-1,0); // Back
	DrawRectangle3d((point3){-h,-w, 0},(point3){ h,-w, l});
	glNormal3d(0, 1,0); // Front
	DrawRectangle3d((point3){-h, w, 0},(point3){ h, w, l});
	glNormal3d(-1,0,0); // Left
	DrawRectangle3d((point3){-w,-h, 0},(point3){-w, h, l});
	glNormal3d( 1,0,0); // Right
	DrawRectangle3d((point3){ w,-h, 0},(point3){ w, h, l});
	// Corners
	glNormal3d(cos(d*5),sin(d*5),0); // Lower Left
	DrawRectangle3d((point3){-w,-h, 0},(point3){-h,-w, l});
	glNormal3d(cos(d*3),sin(d*3),0); // Upper Left
	DrawRectangle3d((point3){-w, h, 0},(point3){-h, w, l});
	glNormal3d(cos(d*1),sin(d*1),0); // Upper Right
	DrawRectangle3d((point3){ w, h, 0},(point3){ h, w, l});
	glNormal3d(cos(d*7),sin(d*7),0); // Lower Right
	DrawRectangle3d((point3){ w,-h, 0},(point3){ h,-w, l});
}

void DrawClamp(double r) {
	glPushMatrix();
		glTranslated(r*1.9,-r/2,0);
			DrawSolidBox(r*2, r/2, r*4);
			glTranslated(0,r,0);
				DrawSolidBox(r*2, r/2, r*4);
	glPopMatrix();
	glRotated(30, 0,0,1);
		DrawCurveBox(r/2, r*4, r*1.25, 300, 10, 0);
	glRotated(-30, 0,0,1);
}

void DrawLinearBearings(double r) {
	glPushMatrix();
		glTranslated(0,0,-r*6);
			DrawSolidCylinder(r*4, r*2, 15, 0); // Right Linear Bearing
			glTranslated(0,0,r*8);
				DrawSolidCylinder(r*4, r*2, 15, 0); // Left Linear Bearing
	glPopMatrix();
}

void DrawLM10UU() {
	glPushMatrix();
		glRotated(90, 0,1,0);
			glTranslated(0,0,-15);
				DrawSolidCylinder(30, 10.5, 15, 0);
	glPopMatrix();
}

void DrawSlider(double r) {
	glPushMatrix();
		DrawLinearBearings(r);
		glTranslated(0,0,-r*6);
		glPushMatrix();
			glTranslated(r*3.5,0,r);
				DrawSolidBox(r*4, r, r*10); // Seperating Spacer
		glPopMatrix();
		glPushMatrix();
			glTranslated(r*2.1,0,0);
				glRotated(90, 0,1,0);
					DrawClamp(r); // Left Tube Mount
					glTranslated(-r*12,0,0);
						glRotated(-180, 0,0,1);
							DrawClamp(r); // Right Tube Mount
						glRotated(180, 0,0,1);
		glPopMatrix();
	glPopMatrix();
}

void DrawTrolley(double r) {
	glPushMatrix();
		glTranslated(-r*6,0,0);
			DrawLinearBearings(r);
			glTranslated(r*12,0,0);
				DrawLinearBearings(r);
				glTranslated(-r*6,0,-r*6);
					DrawSolidBox(r*9, r, r*12); // Seperating Spacer
	glPopMatrix();
}

void DrawCornerMountEdge(double r) {
	glTranslated(0,0,-r*1.25);
		DrawExtrudeTriangle(0,0, 0,r*11, r*11,0, r/2);
	glTranslated(0,0,r*1.25);
}

void DrawCornerMount(double size, double r) {
	glTranslated(-size,-size,0);
		glPushMatrix();
			glTranslated(0,0,-r);
				DrawSolidCylinder(-r*10, r*1.5, 15, 0);
				glTranslated(0,0,r);
					glRotated(-90, 1,0,0);
						glTranslated(0,0,r);
							DrawSolidCylinder(r*10, r*1.5, 15, 0);
							glTranslated(0,0,-r);
								glRotated(90, 0,1,0);
									glTranslated(0,0,r);
										DrawSolidCylinder(r*10, r*1.5, 15, 0);
		glPopMatrix();
		glTranslated(r*4.75,r*10.75,-r*11);
			DrawSolidBox(r*12.5, r/2, r*12.5); // Motor Mount
		glTranslated(-r*4.75,-r*10.75,r*11);
		glTranslated(r*4.75,r*4.75,r);
			DrawSolidBox(r*12.5, r*12.5, r/2); // x  y plane
		glTranslated(-r*4.75,-r*4.75,-r);
		glTranslated(-r*1.25,r*4.75,-r*11);
			DrawSolidBox(r/2, r*12.5, r*12.5); // y -z plane
		glTranslated(r*1.25,-r*4.75,r*11);
		glRotated(-90, 1,0,0);
			DrawCornerMountEdge(r); // x -z plane
		glRotated(90, 1,0,0);
	glTranslated(size,size,0);
}

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glTranslated(-20, -10, 0);
		ExtrudePolygon("makerslide.txt", 10, 0);
	glTranslated(20, 10, 0);
	*/
	
//	gPrinter.DrawCornerAssembly(1);
	
	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
	//RotatePolygon((char*)"v-wheel.txt", 2*PI, 24, 0, 1);
	glNormal3d(0,0,1);
	glBegin(GL_POLYGON);
		glVertex2d(8.0, 5.5);
		glVertex2d(7.7, 5.7);
		glVertex2d(8.0, 6.0);
		glVertex2d(9.5, 6.0);
		glVertex2d(9.5, 4.0);
		glVertex2d(8.5, 3.0);
		glVertex2d(8.0, 3.0);
		glVertex2d(8.0, 5.5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2d(8.0, 0.5);
		glVertex2d(8.0, 3.0);
		glVertex2d(8.5, 3.0);
		glVertex2d(9.5, 2.0);
		glVertex2d(9.5, 0.0);
		glVertex2d(7.0, 0.0);
		glVertex2d(7.0, 0.5);
		glVertex2d(8.0, 0.5);
	glEnd();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);
	glPushMatrix();
	glRotated(90, 1,0,0);
		glTranslated(11.5, 0.5, -20);
			glRotated(90, 0,0,1);
				ExtrudePolygon((char*)"slide.txt", 40, 0);
	glPopMatrix();
	*/
