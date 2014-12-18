#include "Cylinder.h"
#include <GL/glut.h>
#include <time.h>

using namespace std;

Cylinder::Cylinder() {
	height = 1.0;
	ratio = 1.0;
	ratioStep = 1.0;
	radius = 1.0;
}
Cylinder::Cylinder(double height, double radius, double ratio, double ratioStep) {
	this->height = height;
	this->radius = radius;
	this->ratio = ratio;
	this->ratioStep = ratioStep;
}
void Cylinder::render() {
	GLUquadricObj* cyl;
	cyl = gluNewQuadric();
	gluQuadricDrawStyle(cyl, GLU_SMOOTH);
	//srand(time(NULL));

	double randNum = ((double)rand() / (RAND_MAX));
	double randNum2 = ((double)rand() / (RAND_MAX));
	double randNum3 = ((double)rand() / (RAND_MAX));

	glColor3f(randNum, randNum2, randNum3);
	gluCylinder(cyl, radius * ratio, radius * ratio * ratioStep, height, 15, 1);
}
