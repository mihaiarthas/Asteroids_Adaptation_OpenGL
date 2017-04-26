#ifndef BULLET_H
#define BULLET_H

#include "Rocket.h"
#include <vector>
#include "Asteroid.h"

using namespace std;

class Bullet
{
public:
	Bullet(float, float, int, int);
	float x, y;
	int xSpeed;
	int ySpeed;
	int radius;
	int CheckCollision(vector<Asteroid> asteroids);
	bool CheckOffScreen();
	void update();

};
#endif