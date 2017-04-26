#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

class PowerUp
{
public:
	PowerUp(int);
	void update(bool);
	void CheckOffScreen();
	bool CheckBulletCollision(vector<Bullet> bullets);
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

