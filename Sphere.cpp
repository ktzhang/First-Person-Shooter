#include "Sphere.h"
#include <GL/glut.h>

using namespace std;

Sphere::Sphere() {
	this->sphereOrigin = Vector3(0, 0, 0);
	this->sphereRadius = 1;
	r = 1;
	g = 0;
	b = 0;
}
void Sphere::render() {
	glColor3f(r, g, b);
	glutSolidSphere(1, 10, 10);
}


