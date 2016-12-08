#include "Game.h"

bool flip = false;
int current = 1;

Vector3new v1(1.0f, 1.0f, -5.0f);
Vector3new v2(-1.0f, 1.0f, -5.0f);
Vector3new v3(-1.0f, -1.0f, -5.0f);
Vector3new v4(1.0f, -1.0f, -5.0f);
Vector3new v5(1.0f, 1.0f, -15.0f);
Vector3new v6(-1.0f, 1.0f, -15.0f);
Vector3new v7(-1.0f, -1.0f, -15.0f);
Vector3new v8(1.0f, -1.0f, -15.0f);


Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"), primitives(1), m1(1, 0, 0, 0, cos(rotationAngle), sin(rotationAngle), 0, -sin(rotationAngle), cos(rotationAngle))
{
	index = glGenLists(primitives);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning){

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	
	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 0.01f)
	{
		clock.restart();

		Vector3new v1temp(v1.x, v1.y, v1.z + 10);
		Vector3new v2temp(v2.x, v2.y, v2.z + 10);
		Vector3new v3temp(v3.x, v3.y, v3.z + 10);
		Vector3new v4temp(v4.x, v4.y, v4.z + 10);
		Vector3new v5temp(v5.x, v5.y, v5.z + 10);
		Vector3new v6temp(v6.x, v6.y, v6.z + 10);
		Vector3new v7temp(v7.x, v7.y, v7.z + 10);
		Vector3new v8temp(v8.x, v8.y, v8.z + 10);

		v1 = m1 * v1temp;
		v2 = m1 * v2temp;
		v3 = m1 * v3temp;
		v4 = m1 * v4temp;
		v5 = m1 * v5temp;
		v6 = m1 * v6temp;
		v7 = m1 * v7temp;
		v8 = m1 * v8temp;

		v1.z -= 10;
		v2.z -= 10;
		v3.z -= 10;
		v4.z -= 10;
		v5.z -= 10;
		v6.z -= 10;
		v7.z -= 10;
		v8.z -= 10;


		/*if (!flip)
		{
			flip = true;
			current++;
			if (current > primitives)
			{
				current = 1;
			}
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}*/


		cout << "Update up" << endl;
	}
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Cube " << current << endl;
	glLoadIdentity();
	//glRotatef(rotationAngle, 0, 1, 0); // Rotates the camera on Y Axis
	glBegin(GL_QUADS);
	{

		//Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v4.x, v4.y, v4.z);

		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(v5.x, v5.y, v5.z);
		glVertex3f(v6.x, v6.y, v6.z);
		glVertex3f(v7.x, v7.y, v7.z);
		glVertex3f(v8.x, v8.y, v8.z);

		//Complete the faces of the Cube
		//topside
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(v1.x , v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v6.x, v6.y, v6.z);
		glVertex3f(v5.x, v5.y, v5.z);

		//bottom
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(v8.x, v8.y, v8.z);
		glVertex3f(v7.x, v7.y, v7.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v4.x, v4.y, v4.z);

		//left
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glVertex3f(v7.x, v7.y, v7.z);
		glVertex3f(v6.x, v6.y, v6.z);

		//right
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v4.x, v4.y, v4.z);
		glVertex3f(v8.x, v8.y, v8.z);
		glVertex3f(v5.x, v5.y, v5.z);
	}
	glCallList(current);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

