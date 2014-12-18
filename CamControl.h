#ifndef CAMCONTROLL_H_
#define CAMCONTROLL_H_
#pragma once
#include "Matrix4.h"

#include <GL/glut.h>


#include "Matrix4.h"
class CameraController{
public:
	CameraController();

	void updateMouse(int, int);
	void moveForward(double);
	void moveBack(double);
	void moveLeft(double);
	void moveRight(double);
	void apply();
	void updatePrev(int, int);

	Matrix4 getRotX();
	Matrix4 getRotY();
private:
	double sensitivity_x;
	double sensitivity_y;
	double prev_x, prev_y;
	double center_x, center_y;

	Vector4 axis_x, axis_y;
	Matrix4 rotX, rotY;
};

#endif

