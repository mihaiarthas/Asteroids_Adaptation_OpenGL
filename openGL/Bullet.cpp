#include "Bullet.h"
#include <iostream>
#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse 
#include <gl/freeglut.h>
#include <cmath>
#include "Rocket.h"
#include <vector>
#include "Asteroid.h"

using namespace std;

const double PI = 3.14;

Bullet::Bullet(float x, float y, int xSpeed,int ySpeed)
{
	this->x = x;
	this->y = y;
	this->radius = 5;
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
}

void Bullet::update()
{
	this->x += xSpeed;
	this->y += ySpeed;

	glPushMatrix();

		glEnable(GL_POINT_SMOOTH);
		glColor3f(1.0, 1.0, 1.0);


		glBegin(GL_LINE_LOOP);

		for (int i = 0; i < 16; i++) {
			glVertex2d(x + radius * cos(2 * i * PI / 16), y + radius * sin(2 * i * PI / 16));
		}

		glEnd();



	//	glPointSize(radius);
	//	glBegin(GL_POINTS);
	//	glVertex2f(x, y);
	//	glEnd();
		glDisable(GL_POINT_SMOOTH);

	glPopMatrix();

}


int Bullet::CheckCollision(vector<Asteroid> asteroids)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		float distance = sqrt((this->x - asteroids[i].x) * (this->x - asteroids[i].x) + (this->y - asteroids[i].y) * (this->y - asteroids[i].y));
		if (distance <= this->radius + asteroids[i].radius)
		{
			return i;
		}
	}

	return -1;
}

bool Bullet::CheckOffScreen()
{
	if (y > 600 + radius * 4)
		return true;
	return false;
}
