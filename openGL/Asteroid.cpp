#include "Asteroid.h"
#include <windows.h>
#include <gl/freeglut.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

const double PI = 3.14;

Asteroid::Asteroid(int rd)
{
	srand(rd * time(NULL));
	this->x = rand() % 801;
	this->y = rand() % 601;
	this->xSpeed = rand() % 7 - 3;
	this->ySpeed = rand() % 7 - 3;
	this->angle = 0;
	this->radius = 30;


	//cout << x << " " << y << endl;
}

Asteroid::Asteroid(int rd, int rad, Asteroid ast, int i)
{
	srand(rd * time(NULL));
	if (i == 1)
	{
		this->x = ast.x + 15;
		this->y = ast.y + 15;
	}
	else
	{
		this->x = ast.x - 15;
		this->y = ast.y - 15;
	}
	this->xSpeed = rand() % 7 - 3;
	this->ySpeed = rand() % 7 - 3;
	this->angle = 0;
	this->radius = rad;
}



void Asteroid::update()
{
	this->rColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->gColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->bColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	angle += 5;
	x += xSpeed;
	y += ySpeed;

	CheckOffScreen();

	glColor3f(rColor, gColor, bColor);

	glPushMatrix();
		glTranslated(x, y, 0);
		glRotated(angle, 0, 0, 1);
		glTranslated(-x, -y, 0);

		glPushMatrix();


			glBegin(GL_LINE_LOOP);
	
			for (int i = 0; i < 6; i++) {
				glVertex2d(x + radius * cos(2 * i * PI / 6), y + radius * sin(2 * i * PI / 6));
			}

			glEnd();

		glPopMatrix();

	glPopMatrix();

}

void Asteroid::CheckOffScreen()
{
	if (x > 800 + radius) x = 0;
	else if (x < 0 - radius ) x = 800;

	if (y > 600 + radius ) y = 0;
	else if (y < 0 - radius) y = 600;
}
