#include "CamControl.h"
#include <string>
#include <iostream>
using namespace std;

CameraController::CameraController(){
	sensitivity_x = 1.0;
	sensitivity_y = 1.0;

	prev_x = center_x = glutGet(GLUT_WINDOW_WIDTH) / 2.0;
	prev_y = center_y = glutGet(GLUT_WINDOW_HEIGHT) / 2.0;

	axis_x = Vector4(1, 0, 0, 0);
	axis_y = Vector4(0, 1, 0, 0);

	glutWarpPointer(center_x, center_y);
}


void CameraController::apply(){
	//glRotated(rotY, 1, 0, 0);
	//glRotated(rotX, 0, 1, 0);
}

void CameraController::updatePrev(int x, int y){
	prev_x = x;
	prev_y = y;
}

void CameraController::updateMouse(int x, int y){

	cout << "prev  x : " << prev_x << endl;
	cout << "curr x : " << x << endl;
	double diffx = (x - prev_x) * sensitivity_x;
	double diffy = (y - prev_y) * sensitivity_y;
	prev_x = x;
	prev_y = y;

	Matrix4 rot1, rot2;

	//rotY.makeRotateY(diffx);
	//rotX.makeRotateX(diffy);
	string a = "X axis:  ";
	cout << a << axis_x.toString() << endl;
	rotY.makeRotate(-90, Vector3(axis_y.m[0], axis_y.m[1], axis_y.m[2]));
	rot1.makeRotate(-90, Vector3(axis_y.m[0], axis_y.m[1], axis_y.m[2]));
	axis_x = rot1 * axis_x;
	//axis_x.normalize();

	cout << a << axis_x.toString() << endl;


	rotX.makeRotate(-diffy, Vector3(axis_x.m[0], axis_x.m[1], axis_x.m[2]));
	rot2.makeRotate(-diffy, Vector3(axis_x.m[0], axis_x.m[1], axis_x.m[2]));
	axis_y = rot2 * axis_y;
	//axis_y.normalize();
}

void CameraController::moveForward(double val){

}

void CameraController::moveBack(double val){

}
void CameraController::moveLeft(double val){

}

void CameraController::moveRight(double val){

}

Matrix4 CameraController::getRotX(){
	return rotX;
}

Matrix4 CameraController::getRotY(){
	return rotY;
}