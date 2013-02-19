void DrawMakinatorV0(double mSize, double mX, double mY, double mZ, bool thin) {
	double size = thin ? 20 : 40;
	double length = thin ? mSize+44 : mSize+64;
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray50);
	glPushMatrix(); // X Axis Extrisions
		glTranslated(0,length/2,mSize/2+20);
			DrawSolidBox(mSize+30, size, 20);
			glTranslated(0,-length,0);
				DrawSolidBox(mSize+30, size, 20);
				glTranslated(0,0,-mSize-40);
			DrawSolidBox(mSize+30, size, 20);
			glTranslated(0,length,0);
		DrawSolidBox(mSize+30, size, 20);
	glPopMatrix();
	glPushMatrix(); // Z Axis Legs
		glTranslated(mSize/2+15,-length/2,-mSize/2);
			DrawSolidBox(40,size,mSize+20);
			glTranslated(-mSize-30,0,0);
				DrawSolidBox(40,size,mSize+20);
				glTranslated(0,length,0);
			DrawSolidBox(40,size,mSize+20);
			glTranslated(mSize+30,0,0);
		DrawSolidBox(40,size,mSize+20);
	glPopMatrix();
	glPushMatrix(); // Y Axis Makerslides and Extrusions
		length = thin ? mSize+64 : mSize+104;
		glTranslated(mSize/2+25,0,mSize/2);
			DrawSolidBox(20, length, 40); // +X Upper
			glTranslated(-mSize-50,0,0);
				DrawSolidBox(20, length, 40); // -X Upper
				glTranslated(0,0,-mSize-20);
			DrawSolidBox(20, length, 20); // -X Lower
			glTranslated(mSize+50,0,0);
		DrawSolidBox(20, length, 20); // +X Lower
	glPopMatrix();
	color(darkGreen);
	glPushMatrix(); // X Carriage
		glTranslated(mX+15, mY-30, mSize/2+52);
			DrawLM10UU(); // Q4
			glTranslated(-30, 0, 0);
				DrawLM10UU(); // Q3
				glTranslated(0, 60, 0);
			DrawLM10UU(); // Q2
			glTranslated(30, 0, 0);
		DrawLM10UU(); // Q1
	glPopMatrix();
	color(silver);
	glPushMatrix(); // X Axis Rods
		glTranslated(0,mY,mSize/2+52);
			glRotated(90, 0,1,0);
				glTranslated(0,-30,-mSize/2-30);
					DrawSolidCylinder(mSize+60, 5, 10, 1); // -Y
					glTranslated(0,60,0);
						DrawSolidCylinder(mSize+60, 5, 10, 1); // +Y
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ivery);
	glPushMatrix(); // Y Axis Wheel Carriage
		glTranslated(0,mY,mSize/2+20);
			glRotated(-90, 0,1,0);
				glTranslated(0,0,-mSize/2-44);
					DrawSolidBox(80, 80, 4);
					glTranslated(0,0,mSize+84);
						DrawSolidBox(80, 80, 4);
	glPopMatrix();
	color(lightRed);
	glPushMatrix(); // Z Axis Plate (Print Bed)
		glTranslated(0, 0, mZ+20);
			DrawSolidBox(mSize+20, mSize+20, 4);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray25);
	glPushMatrix(); // Z Axis Platform
		length += 1;
		glTranslated(0, mSize/2+5, mZ);
			DrawSolidBox(mSize+20, 4, 20); // +X
			glTranslated(0, -mSize-10, 0);
				DrawSolidBox(mSize+20, 4, 20); // -X
				glTranslated(-mSize/2+10, mSize/2+5, 0);
					DrawSolidBox(4, length, 20); // -Y
					glTranslated(mSize-20, 0,0);
						DrawSolidBox(4, length, 20); // +Y
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	glPushMatrix(); // Y Axis V Wheels Right
		glTranslated(mSize/2+30,mY,mSize/2-12);
			glRotated(90, 0,1,0);
				DrawSolidCylinder(8, 12, 15, 0); // Lower
				glTranslated(-64,-30,0);
					DrawSolidCylinder(8, 12, 15, 0); // Near
					glTranslated(0,60,0);
						DrawSolidCylinder(8, 12, 15, 0); // Far
	glPopMatrix();
	glPushMatrix(); // Y Axis V Wheels Left
		glTranslated(-mSize/2-30,mY,mSize/2-12);
			glRotated(-90, 0,1,0);
				DrawSolidCylinder(8, 12, 15, 0); // Lower
				glTranslated(64,-30,0);
					DrawSolidCylinder(8, 12, 15, 0); // Near
					glTranslated(0,60,0);
						DrawSolidCylinder(8, 12, 15, 0); // Far
	glPopMatrix();
	glPushMatrix(); // Print Area Outline
		glTranslated(0,0,mZ+25);
			DrawRectangle(-mSize/2,-mSize/2, mSize/2,mSize/2, 1);
	glPopMatrix();
	glPushMatrix(); // X Axis Pulleys
		glTranslated(0,mY-50,mSize/2+52);
			glRotated(90, 1,0,0);
				glTranslated(-mSize/2-60,0,0);
					DrawPulley(10, 5);
					glTranslated(mSize+125,0,0);
						DrawPulley(10, 5);
	glPopMatrix();
	glPushMatrix(); // Y Axis Pulleys
		length = thin ? mSize+105 : mSize+145;
		glTranslated(0,0,mSize/2+19.5);
			glRotated(90, 0,1,0);
				glTranslated(0,-length/2,-mSize/2-49);
					DrawPulley(10, 5);
					glTranslated(0,length,0);
						DrawPulley(10, 5);
						glTranslated(0,0,mSize+98);
					DrawPulley(10, 5);
					glTranslated(0,-length,0);
				DrawPulley(10, 5);
	glPopMatrix();
	glPushMatrix(); // X Motor
		glTranslated(mSize/2+65, mY-35, mSize/2+52);
			glRotated(-90, 1,0,0);
				DrawMotor(false);
	glPopMatrix();
	glPushMatrix(); // Y Motors
		glTranslated(0, thin ? -mSize/2-53 : -mSize/2-73, mSize/2+19);
			glRotated(90, 0,1,0);
				glTranslated(0,0,-mSize/2-35);
					DrawMotor(false);
					glTranslated(0,0,mSize+70);
						glRotated(180, 0,1,0);
							DrawMotor(false);
	glPopMatrix();
	glPushMatrix(); // Z Motors
		glTranslated(-mSize/2+60,mSize/2+32,-mSize/2+22);
			glRotated(90, 0,1,0);
				DrawMotor(false); // Q4
				glTranslated(0,-mSize-64,0);
					DrawMotor(false); // Q3
					glTranslated(0,0,mSize-120);
				glRotated(180, 0,1,0);
			DrawMotor(false); // Q2
			glTranslated(0,mSize+64,0);
		DrawMotor(false); // Q1
	glPopMatrix();
	color(yellow);
	glPushMatrix(); // Z Screws
		glTranslated(mSize/2-23, -mSize/2-32, -mSize/2);
			DrawSolidCylinder(mSize+20, 4, 10, 1); // Q4
			glTranslated(-mSize+46,0,0);
				DrawSolidCylinder(mSize+20, 4, 10, 1); // Q3
				glTranslated(0,mSize+64,0);
			DrawSolidCylinder(mSize+20, 4, 10, 1); // Q2
			glTranslated(mSize-46,0,0);
		DrawSolidCylinder(mSize+20, 4, 10, 1); // Q1
	glPopMatrix();
	color(lightBlue);
	glPushMatrix(); // X Axis Belt
		glTranslated(2,mY-50,mSize/2+45);
			DrawSolidBox(mSize+125, 10, 2);
			glTranslated(0,0,12);
				DrawSolidBox(mSize+125, 10, 2);
	glPopMatrix();
	glPushMatrix(); // Y Axis Belts
		length = thin ? mSize+105 : mSize+145;
		glTranslated(-mSize/2-49, 0, mSize/2+24.5);
			DrawSolidBox(10, length, 2);
			glTranslated(0,0,-12);
				DrawSolidBox(10, length, 2);
				glTranslated(mSize+98,0,0);
			DrawSolidBox(10, length, 2);
			glTranslated(0,0,12);
		DrawSolidBox(10, length, 2);
	glPopMatrix();
	glPushMatrix(); //
	glPopMatrix();
}
