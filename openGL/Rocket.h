#ifndef ROCKET_H
#define ROCKET_H

class Rocket
{
public:
	Rocket();
	float angle;
	float x, y;
	int height;
	int base;
	int heading;
	float rColor, bColor, gColor;
	float speed;
	void draw_rocket(bool);
	void move(int);
	void CheckOffScreen();
};

#endif