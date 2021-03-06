// This saves the contents of an OpenGL screen to a .ppm picture file.
// Bart Stander
// April, 2008
//
// Vertical ordering swiched:
// February, 2011
// Nick Cox

// FastSave updated March of 2011, so the picture is not upside down (thanks Nick Cox), and
// this version is MANY times faster than the previous, because it uses binary ppm, and fout.write

#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
#include "save.h"

bool Save() {
	static int huns = 0;
	static int tens = 0;
	static int ones = 1;

	char file[13] = "File000.ppm";
	file[4] = '0' + huns;
	file[5] = '0' + tens;
	file[6] = '0' + ones;
	int stime = time(0);
	bool completed = SaveToPPM(file);
	stime = time(0)-stime;
	cout << "Comleted in " << stime << " ms.\n";
	ones++;
	if(ones > 9) {
		ones = 0;
		tens++;
	}
	if(tens > 9) {
		tens = 0;
		huns++;
	}
	return completed;
}

bool SaveToPPM(char filename[]) {
	struct Pixel {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
	cout << "Saving to binary ppm file " << filename << " ...\n";
	
	// Allocate enough space to hold the whole screen
	int area = gX*gY;
	Pixel *pixels = new Pixel[area];
	Pixel *pixelsFlipped = new Pixel[area];
	
	// reads from the framebuffer into pixels (from the lower left corner)
	glReadPixels(0,0,gX,gY,GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
	// Open the output file
	ofstream fout(filename, ios::binary);
	if(!fout)
		return false;
	
	// Note that we must flip the vertical order and write from top to bottom.
	for(int y=0; y<gY; y++) {
		int yflipped = gY-y-1;
		int index = y*gX;
		int indexFlipped = yflipped*gX;
		for(int x=0; x<gX; x++) {
			pixelsFlipped[indexFlipped+x] = pixels[index+x];
		}
	}
	
	// write the ppm header
	fout << "P6" << endl; // p3 for text, p6 for binary
	fout << gX << " " << gY << endl;
	fout << "255" << endl;
	
	// write the ppm color data.
	fout.write( (char*)pixelsFlipped, gX*gY*3 );
	fout.flush();
	// cleanup
	fout.close();
	delete []pixels;
	delete []pixelsFlipped;
	
	cout << "Done saving.\n";
	
	return true;
}

bool SlowSaveToPPM(char filename[]) {
	struct Pixel {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	};
	cout << "Saving to ppm file " << filename << " ..." << endl;
	
	// Allocate enough space to hold the whole screen
	int area = gX*gY;
	Pixel *pixels = new Pixel[area];
	
	// reads from the framebuffer into pixels (from the lower left corner)
	glReadPixels(0,0,gX,gY,GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
	// Open the output file
	ofstream fout(filename);
	if(!fout)
		return false;
	
	// write the ppm header
	fout << "P3" << endl;
	fout << gX << " " << gY << endl;
	fout << "255" << endl;
	
	// write the ppm color data.
	// Note that we must switch the vertical order and write from top to bottom.
	
	// Start the index at the begining of the last line
	int index=gX*gY - gX;
	
	for(int y=0; y<gY; y++) {
		for(int x=0; x<gX; x++) {
			fout << (int)pixels[index].r << " " << (int)pixels[index].g << " " << (int)pixels[index].b << endl;
			index++;
		}
		// Back up to the begining of the previous line
		index -= 2*gX;
	}
	
	// cleanup
	delete []pixels;
	
	cout << "Done saving.\n";
	
	return true;
}
