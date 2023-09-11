#pragma once

#include <allegro5/allegro.h>

class Color
{
public:
	Color(int r, int g, int b, int a);
	~Color() {};
	int getR() { return mR; }
	int getG() { return mG; }
	int getB() { return mB; }
	int getA() { return mA; }
private:
	int mR, mG, mB, mA;
};
