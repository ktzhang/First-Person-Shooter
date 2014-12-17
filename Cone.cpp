#include "Cone.h"
#include <GL/glut.h>

using namespace std;
void Cone::render() {
	glColor3f(1, 0, 0);
	glutSolidCone(CONE_BASE, CONE_HEIGHT, 10, 10);
}