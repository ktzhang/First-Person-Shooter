#include "Sphere.h"
#include <GL/glut.h>

using namespace std;

Sphere::Sphere() {
	this->sphereOrigin = Vector3(0, 0, 0);
	this->sphereRadius = 1;
}
void Sphere::render() {
	glColor3f(1, 0, 0);
	glutSolidSphere(1, 10, 10);
}


