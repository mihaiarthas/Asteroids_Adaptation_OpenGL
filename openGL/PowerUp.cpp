#include "PowerUp.h"
#include <time.h>
#include <gl/freeglut.h>
#include <vector>
#include "Bullet.h"

PowerUp::PowerUp(int rd)
{
	srand(rd * time(NULL));
	this->x = rand() % 801;
	this->y = rand() % 601;
	this->xSpeed = rand() % 8 - 3;
	this->ySpeed = rand() % 8 - 3;
	this->radius = 20;
}

void PowerUp::update(bool powerBool)
{
	if (powerBool == false)
	{
		this->rColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		this->gColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		this->bColor = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		x += xSpeed;
		y += ySpeed;

		CheckOffScreen();

		glPushMatrix();

		glColor3f(rColor, gColor, bColor);


		glBegin(GL_POLYGON);

		glVertex2f(x - radius, y);
		glVertex2f(x, y - radius);
		glVertex2f(x + radius, y);
		glVertex2f(x, y + radius);


		glEnd();

		glPopMatrix();
	}
	
	else return;
}

bool PowerUp::CheckBulletCollision(vector<Bullet> bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		float distance = sqrt((this->x - bullets[i].x) * (this->x - bullets[i].x) + (this->y - bullets[i].y) * (this->y - bullets[i].y));
		if (distance <= this->radius + bullets[i].radius)
		{
			return true;
		}
	}

	return false;
}

void PowerUp::CheckOffScreen()
{
	if (x > 800 + radius) x = 0;
	else if (x < 0 - radius) x = 800;

	if (y > 600 + radius) y = 0;
	else if (y < 0 - radius) y = 600;
}
