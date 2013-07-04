#pragma once
#include <string>

// Z Axis steps/mm (m10 threaded rod, 1:1 gearing, 0 microstepping)
// 10 rev    1 cm   200 steps
// ------ x ----- x --------- = 200 steps/mm
//  1 cm    10 mm     1 rev

enum displayList {
	PULLEY=100,
	MOTOR
};

class Printer {
private:
	bool mPause;
	double mSize, mArea, mX, mY, mZ, mR;
	unsigned mType;
	bool mOption[3];
	string mOptions[7],  mTitles[7];
	
	void DrawCrossMount();
	double zeroToOne(double n);
public:
	Printer();
	~Printer();
	void DrawCornerAssembly(int t);
	void Draw();
	void InitDisplayLists();
	void Pause(bool p);
	bool Pause();
	void Set(double x, double y, double z);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);
	void SetType(unsigned type);
	void SetSize(double size);
	double GetSize();
	string Title();
	string Options();
	void Option(char o);
};
