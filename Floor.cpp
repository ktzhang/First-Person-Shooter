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
using namespace std;

void Floor::render() {
	glColor3f(1, 1, 1);
	float sideLength = 10;
	int startX;
	int startZ;
	glBegin(GL_QUADS);
	for (int i = 0; i < numSquares; i++) {
		for (int j = 0; j < numSquares; j++) {
			glNormal3f(0, 1, 0);
			startX = i / sideLength;
			startZ = j / sideLength;
			
			glVertex3f(startX, 0, startZ);
			glVertex3f(startX+ (1 / sideLength), 0, startZ);
			glVertex3f(startX + (1 / sideLength), 0, startZ + (1 / sideLength));
			glVertex3f(startX, 0, startZ + (1 / sideLength));
		}
	}
	glEnd();
}