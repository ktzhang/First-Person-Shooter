#include "Cylinder.h"
#include <GL/glut.h>

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
	gluQuadricDrawStyle(cyl, GLU_LINE);
	glColor3f(1, 0, 0);
	gluCylinder(cyl, radius * ratio, radius * ratio * ratioStep, height, 15, 1);
}
