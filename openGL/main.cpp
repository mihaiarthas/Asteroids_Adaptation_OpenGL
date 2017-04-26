#include <windows.h>
#include <MMSystem.h>
#include <gl/freeglut.h>
#include <iostream>
#include <time.h>
//#include "Asteroid.h"
#include <vector>
#include "Rocket.h"
#include "Bullet.h"
#include "PowerUp.h"

#define FPS 60


using namespace std;

const int HEIGHT = 800;
const int WIDTH = 600;

int direction = 0;
bool rocketShoot = false;

Rocket Rocky;
int asteroidsNumber = 10;
bool powerBool = false;

int initialTime = time(NULL);
int finalTime;
int frameCount = 0;

int shootTime = time(NULL);
int afterTime;
int nextTimeShoot = 0;
int CurrentTime = time(NULL);

vector<PowerUp> powerUp;
vector<Bullet> bullets;
vector<Asteroid> bigAsteroids;


void init(void)  // initializare fereastra de vizualizare
{
	//glClearColor(0.098, 0.098, 0.439, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glClearColor(0.0, 0.0, 0.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glMatrixMode(GL_PROJECTION); // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0, HEIGHT, 0, WIDTH); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

}
void MyKeyboardFunc(unsigned char Key, int x, int y)
{
	if (Key == ' ')
	{
		sndPlaySound("smb_fireball.wav", SND_ASYNC);
		if (powerBool == true)
		{
			bullets.push_back(Bullet(Rocky.x, Rocky.y, 0, 10));
			bullets.push_back(Bullet(Rocky.x, Rocky.y, 3, 10));
			bullets.push_back(Bullet(Rocky.x, Rocky.y, -3, 10));
		}
		else
		{
			bullets.push_back(Bullet(Rocky.x, Rocky.y, 0, 10));
		}

	}
}


bool asteroidCollision(Asteroid a1, Asteroid a2)
{
	float distance = sqrt((a1.x - a2.x) * (a1.x - a2.x) + (a1.y - a2.y) * (a1.y - a2.y));

	if (distance <= a1.radius + a2.radius)
	{
		return true;
	}
	return false;
}

bool rocketAsteroidCollision(Asteroid a, Rocket r)
{
	float ypeek = r.y + 2 * (r.height / 3);
	float dist = sqrt((a.x - r.x)*(a.x - r.x) + ((a.y - ypeek)*(a.y - ypeek)));
	if (dist <= a.radius + ypeek)
	{
		return true;
	}
	return false;
}
void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	shootTime = time(NULL);


	Rocky.draw_rocket(powerBool);
	Rocky.move(direction);

	for (int i = 0; i < powerUp.size(); i++)
	{
		powerUp[i].update(powerBool);
		if (powerBool == false)
		{
			if (powerUp[i].CheckBulletCollision(bullets) == true)
			{
				sndPlaySound("smb_powerup.wav", SND_ASYNC);
				powerBool = true;
			}
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].update();
		int ast = bullets[i].CheckCollision(bigAsteroids);

		if (ast != -1)
		{
			if (bigAsteroids[ast].radius == 30)
			{
				bigAsteroids.push_back(Asteroid(ast + 1, 15, bigAsteroids[ast], 1 ));
				bigAsteroids.push_back(Asteroid(ast + ast, 15, bigAsteroids[ast], 2 ));
			}
			bigAsteroids.erase(bigAsteroids.begin() + ast);
			bullets.erase(bullets.begin() + i);

			sndPlaySound("bangSmall.wav", SND_ASYNC);

		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].CheckOffScreen() == true)
		{
			bullets.erase(bullets.begin() + i);
		}
	}


	for (int i = 0; i < bigAsteroids.size(); i++)
	{
		bigAsteroids[i].update();
	}

	for (int i = 0; i < bigAsteroids.size(); i++)
	{
		for (int j = i + 1; j < bigAsteroids.size(); j++)
		{
			if (asteroidCollision(bigAsteroids[i], bigAsteroids[j]) == true)
			{
				bigAsteroids[i].xSpeed *= -1;
				bigAsteroids[i].ySpeed *= -1;

				bigAsteroids[j].xSpeed *= -1;
				bigAsteroids[j].ySpeed *= -1;
			}
		}
	}
	glutSwapBuffers();
	frameCount++;
	finalTime = time(NULL);
	if (finalTime - initialTime >= 1)
	{
		cout << "FPS : " << frameCount / (finalTime - initialTime) << endl;
		frameCount = 0;
		initialTime = finalTime;
	}


	// Game OVER
	for (int i = 0; i < bigAsteroids.size(); i++)
	{
		if (rocketAsteroidCollision(bigAsteroids[i], Rocky) == true)
		{
			bigAsteroids[i].xSpeed *= -1;
			bigAsteroids[i].ySpeed *= -1;

		}

	}

}

void OnMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		direction = -10;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		direction = 10;
	}
	else
	{
		direction = 0;
	}

	glDisable(GL_SMOOTH);
}




void idle(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, idle, 0);
}

void main(int argc, char** argv)
{
	for (int i = 0; i < asteroidsNumber; i++)
	{
		bigAsteroids.push_back(Asteroid(i));
	}
	powerUp.push_back(PowerUp(time(NULL)));

	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(HEIGHT, WIDTH); // dimensiunile ferestrei 
	glutCreateWindow("Asteroids"); // creeaza fereastra 
	init();
	glutMouseFunc(OnMouseClick);
	glutKeyboardFunc(MyKeyboardFunc);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glutDisplayFunc(Draw); // procedura desen este invocata ori de cate ori este nevoie
	glutTimerFunc(1000 / FPS, idle, 0);
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

}

