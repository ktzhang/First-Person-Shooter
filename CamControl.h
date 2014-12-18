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
	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void apply();
	void updatePrev(int, int);

	Matrix4 getRotX();
	Matrix4 getRotY();
	Matrix4 getTranslation();
	Vector3 getPosition();

	double getAngleX();
	double getAngleY();
private:
	double sensitivity_x;
	double sensitivity_y;
	double prev_x, prev_y;
	double center_x, center_y;
	double px, py, pz;

	double step;
	double angleX, angleY;

	Vector4 axis_x, axis_y;
	Matrix4 rotX, rotY, trans;
};

#endif

