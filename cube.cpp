#include "Cube.h"
#include "Matrix4.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include <GL/glut.h>
#include "Cube.h"
#include <math.h>       /* sqrt */

const double Cube::SIDELEN = 10;

using namespace std;
Cube::Cube() {
	sideLen = SIDELEN;
	calcBoundingSphereRadius();
	this->color = { 1, 1, 1 };
}

Cube::Cube(Color color) {
	sideLen = 10.0;
	calcBoundingSphereRadius();
	this->color = color;
}


void Cube::calcBoundingSphereRadius(){
	sphereRadius = sqrt(3 * sideLen*sideLen) / 2;
}

void Cube::render() {
	// Pushing and popping the matrix
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, sideLen / 2);
	glVertex3f(-sideLen / 2, -sideLen / 2, sideLen / 2);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(-sideLen / 2, sideLen / 2, -sideLen / 2);
	glVertex3f(-sideLen / 2, -sideLen / 2, -sideLen / 2);
	glVertex3f(-sideLen / 2, -sideLen / 2, sideLen / 2);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(sideLen / 2, sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, sideLen / 2);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-sideLen / 2, sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, -sideLen / 2);
	glVertex3f(-sideLen / 2, -sideLen / 2, -sideLen / 2);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(sideLen / 2, sideLen / 2, sideLen / 2);
	glVertex3f(sideLen / 2, sideLen / 2, -sideLen / 2);
	glVertex3f(-sideLen / 2, sideLen / 2, -sideLen / 2);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-sideLen / 2, -sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, -sideLen / 2);
	glVertex3f(sideLen / 2, -sideLen / 2, sideLen / 2);
	glVertex3f(-sideLen / 2, -sideLen / 2, sideLen / 2);
	glEnd();
}