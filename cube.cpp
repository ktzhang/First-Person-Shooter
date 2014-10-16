#include "Cube.h"
#include "Matrix4.h"

using namespace std;

Cube::Cube()
{
	spinDirection = -1;
  angle = 0.0;
  origin[0] = 0;
  origin[1] = 0;
  origin[2] = 0;
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}

void Cube::animate() {
	spin(spinDirection);
	//horizontalTransform(0);
}

void Cube::spin(double deg)   // deg is in degrees
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  model2world.makeRotateY(angle);   // This creates the matrix to rotate the cube
}

void Cube::horizontalTransform(double amount) {
	model2world.makeTranslate(origin[0] += amount, 0, 0);
}
