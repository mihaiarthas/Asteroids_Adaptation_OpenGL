#pragma once
#include <string>

class Asteroid
{
public:
	Asteroid(int rd);
	Asteroid(int rd, int rad, Asteroid ast,int i);
	void update();
	void CheckOffScreen();
	double x;
	double y;
	double xSpeed;
	double ySpeed;
	double angle;
	int radius;
	float rColor;
	float gColor;
	float bColor;
};