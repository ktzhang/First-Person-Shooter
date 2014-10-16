#include "Cube.h"
#include "Matrix4.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Vector3.h"
#include "Vector4.h"


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


void Cube::changeSpinDirection() {
	spinDirection = -spinDirection;
}

void Cube::animate() {
	Matrix4 horizontal;
	horizontal.makeTranslate(origin[0], origin[1], origin[2]);
	//horizontal.makeTranslate(0.01, 0.01, 0.01);
	Matrix4 rotate = spin(spinDirection);
	model2world =  horizontal * rotate;
	
	Matrix4 scale;
	scale.makeScale(1.001, 1.001, 1.001);
	//model2world = scale;
}

Matrix4 Cube::spin(double deg)   // deg is in degrees
{
	Matrix4 base;
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  base.makeRotateY(angle);   // This creates the matrix to rotate the cube
  return base;
}

void Cube::horizontalTransform(double x, double y, double z) {
	origin[0] = origin[0] + x;
	origin[1] = origin[1] + y;
	origin[2] = origin[2] + z;
	OutputDebugString(to_string(origin[0]).c_str());
}
