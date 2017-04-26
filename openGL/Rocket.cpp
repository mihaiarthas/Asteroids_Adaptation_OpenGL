#include "Rocket.h"
#include <iostream>
#include <windows.h>  // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse
#include <gl/freeglut.h>
#include <cmath>

using namespace std;

const float M_PI = 3.1415926535897;

Rocket::Rocket()
{
	this->angle = 15;
	this->x = 400;
	this->y = 20;
	this->base = 36;
	this->height = 48;
	this->heading = 90;
	this->speed = 10;
}
void Rocket::draw_rocket(bool powerBool)
{
	CheckOffScreen();

	glColor3f(1.0, 1.0, 1.0);

	//heading++;

	glPushMatrix();
		


		glPushMatrix();

			glBegin(GL_LINE_LOOP);
			glVertex2f(x, y + (2 * height / 3));
			glVertex2f(x - base / 2, y - height / 3);
			glVertex2f(x + base / 2, y - height / 3);
			glEnd();

			if (powerBool == true)
			{
				this->rColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				this->gColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				this->bColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				glColor3f(rColor, gColor, bColor);

				glBegin(GL_LINE_LOOP);
				
				glVertex2f(x - base, y);
				glVertex2f(x, y - base);
				glVertex2f(x + base, y);
				glVertex2f(x, y + base);

				glEnd();
			}

		glPopMatrix();

	glPopMatrix();

}

void Rocket::move(int direction)
{
	x += direction;
}

void Rocket::CheckOffScreen()
{
	if (x <= 0 + base)
	{
		x = base;
	}

	if (x >= 800 - base)
	{
		x = 800 - base;
	}
}
