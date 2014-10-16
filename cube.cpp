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
	reset();
}

Matrix4& Cube::getMatrix()
{
  return model2world;
}


void Cube::changeSpinDirection() {
	spinDirection = -spinDirection;
}

void Cube::reset() {
	spinDirection = -1;
	spinAngle = 0.0;
	scale = 1;
	orbitAngle = 0.0;
	origin[0] = 0;
	origin[1] = 0;
	origin[2] = 0;
}

void Cube::animate() {
	//Translate
	Matrix4 translateMatrix;
	translateMatrix.makeTranslate(origin[0], origin[1], origin[2]);

	Matrix4 rotateMatrix;
	rotateMatrix.makeRotateY(spinAngle += spinDirection * 1);   // This creates the matrix to rotate the cube

	Matrix4 orbitMatrix;
	orbitMatrix.makeRotateZ(orbitAngle);

	Matrix4 scaleMatrix;
	scaleMatrix.makeScale(scale, scale, scale);

	model2world = orbitMatrix * translateMatrix * scaleMatrix * rotateMatrix;
	
	//model2world = scale;
}

void Cube::spin(double deg) {  // deg is in degrees{
	spinAngle += deg;
	if (spinAngle > 360.0 || spinAngle < -360.0) spinAngle = 0.0;
}

void Cube::orbitCube(double deg) {
	orbitAngle += deg;
	if (orbitAngle > 360.0 || orbitAngle < -360.0) orbitAngle = 0.0;
}

void Cube::scaleCube(double amount) {
	scale += amount;
}

void Cube::translateCube(double x, double y, double z) {
	origin[0] = origin[0] + x;
	origin[1] = origin[1] + y;
	origin[2] = origin[2] + z;
	OutputDebugString(to_string(origin[0]).c_str());
}
