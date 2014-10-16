#include "Cube.h"
#include "Matrix4.h"

using namespace std;

Cube::Cube()
{
  angle = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}

void Cube::spin(double deg)   // deg is in degrees
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  model2world.makeRotateY(angle);   // This creates the matrix to rotate the cube
}
