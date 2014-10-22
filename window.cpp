#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here


//----------------------------------------------------------------------------
// Callback method of keyboard input
void Window::processNormalKeys(unsigned char key, int x, int y) 
{
	double transFactor = 0.5;
	double orbitDeg = 10;
	double scaleFactor = 0.1;
	switch (key) {
		//'t' for spinning clockwise or counter clockwise
	case 116:
		Globals::cube.changeSpinDirection();
		break;

		//'x' left 
	case 120:
		Globals::cube.translateCube(-transFactor, 0, 0);
		break;

		// 'X' right
	case 88:
		Globals::cube.translateCube(transFactor, 0, 0);
		break;

		// 'y' down 
	case 121:
		Globals::cube.translateCube(0, -transFactor, 0);
		break;

		// 'Y' up
	case 89:
		Globals::cube.translateCube(0, transFactor, 0);
		break;

		// 'z' in
	case 122:
		Globals::cube.translateCube(0, 0, transFactor);
		break;

		// 'Z' out
	case 90:
		Globals::cube.translateCube(0, 0, -transFactor);
		break;

		// 'r' reset
	case 114:
		Globals::cube.reset();
		break;

		// 'o' orbit counterclockwise
	case 111:
		Globals::cube.orbitCube(-orbitDeg);
		break;

		// 'O' orbit clockwise
	case 79:
		Globals::cube.orbitCube(orbitDeg);
		break;


		// 's' scale down
	case 115:
		Globals::cube.scaleCube(-scaleFactor);
		break;

		// 'S' scale up
	case 83:
		Globals::cube.scaleCube(scaleFactor);
		break;
	}
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{

	Globals::cube.animate();   // rotate cube; if it spins too fast try smaller values and vice versa
	displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode



	// Tell OpenGL what ModelView matrix to use:
	//Matrix4 glmatrix;
	//glmatrix = Globals::cube.getMatrix();

	Vector3 cameraCenterVector = Vector3(0, 10, 10);
	Vector3 cameraDVector = Vector3(0, 0, 0);
	Vector3 cameraUpVector = Vector3(0, 1, 0);

	Camera camera;
	camera.eVector = cameraCenterVector;
	camera.dVector = cameraDVector;
	camera.upVector = cameraUpVector;

	Matrix4 cameraMatrix = *(camera.getGLMatrix());
	glLoadMatrixd(cameraMatrix.getPointer());

	std::string hiThere = "\n";
	cameraMatrix.print(hiThere);
	OutputDebugString(hiThere.c_str());
	//glLoadMatrixd(glmatrix.getPointer());

	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}
