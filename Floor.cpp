#include "Floor.h"
#include <GL/glut.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "Group.h"
#include "Geode.h"
#include "Sphere.h"
#include "cube.h"
#include "MatrixTransform.h"
#include "Robot.h"
#include "Camera.h"

#include "Vector3.h"

extern GLuint * bottom;
extern GLuint * top;
using namespace std;


void Floor::render() {
	glColor3f(1, 1, 1);
	int numSquares = 5;
	float sideLength = 2;
	float startX;
	float startZ;
	float increment = sideLength / numSquares;
	glActiveTexture(GL_TEXTURE0);
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			glColor3f(1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, *bottom);
	glBegin(GL_QUADS);
	for (int i = 0; i < numSquares; i++) {
		for (int j = 0; j < numSquares; j++) {
			glNormal3f(0, 1, 0);
			startX = (float)i * increment - sideLength / 2;
			startZ = (float)j * increment - sideLength / 2;
			glTexCoord2f(0, 1); glVertex3f(startX, 0, startZ);
			glTexCoord2f(1, 1); glVertex3f(startX + increment, 0, startZ);
			glTexCoord2f(1, 0); glVertex3f(startX + increment, 0, startZ + increment);
			glTexCoord2f(0, 0); glVertex3f(startX, 0, startZ + increment);
		}
	}
	glEnd();
			//glEnable(GL_BLEND);
}