#include "CamControl.h"
#include <string>
#include <iostream>
using namespace std;

CameraController::CameraController(){
	sensitivity_x = 0.2;
	sensitivity_y = 0.2;

	prev_x = center_x = glutGet(GLUT_WINDOW_WIDTH) / 2.0;
	prev_y = center_y = glutGet(GLUT_WINDOW_HEIGHT) / 2.0;

	axis_x = Vector4(1, 0, 0, 0);

	px = py = pz = 0;
	angleX = 3.14159265259 / 2.0;
	angleY = 0;
	step = 0.02;

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
	//cout << "prev  x : " << prev_x << endl;
	//cout << "curr x : " << x << endl;
	double diffx = (x - prev_x) * sensitivity_x;
	double diffy = (y - prev_y) * sensitivity_y;
	double width = glutGet(GLUT_WINDOW_WIDTH);
	if (x >= width - 2 || x < 2){
		glutWarpPointer(width / 2, y);
		prev_x = width / 2;
		prev_y = y;
		return;
	}
	double height = glutGet(GLUT_WINDOW_HEIGHT);
	if (y >= height - 2 || y < 2){
		glutWarpPointer(x,height/2.0);
		prev_x = x;
		prev_y = height / 2.0;
		return;
	}
	prev_x = x;


	double newX = angleX + diffx * 3.14159265359 / 180.0;
	double newY = angleY - diffy * 3.14159265359 / 180.0;

	if (newY > 0.95 || newY < -1) {
		diffy = 0;
	}
	else {
		prev_y = y;
	}

	angleX += diffx * 3.14159265359 / 180.0;
	angleY -= diffy * 3.14159265359 / 180.0;

	Matrix4 rot1, rot2;

	//rotY.makeRotateY(diffx);
	//rotX.makeRotateX(diffy);
	//string a = "\nX axis:  ";
	//cout << a << axis_x.toString() << endl;
	rotX.makeRotateY(-diffx);
	//rot1.makeRotate(-diffx, Vector3(axis_y.m[0], axis_y.m[1], axis_y.m[2]));
	//axis_x.normalize();

	//cout << "\nDiff X " << diffx << " DiffY " << diffy << "\n";

	axis_x = rotX * axis_x;

	rotY.makeRotate(-diffy, Vector3(axis_x.m[0], axis_x.m[1], -axis_x.m[2]));
	//rot2.makeRotate(-diffy, Vector3(axis_x.m[0], axis_x.m[1], axis_x.m[2]));
	//axis_y = rot2 * axis_y;
	//cout << "\nY axis:" << axis_y.toString() << endl;
	//axis_y.normalize();
}

double constValue = 0.95;

void CameraController::moveForward(){
	pz += sin(angleX) * step;
	px += cos(angleX) * step;
	if (pz > constValue) pz = constValue;
	else if (pz < -constValue) pz = -constValue;
	if (px > constValue) px = constValue;
	else if (px < -constValue) px = -constValue;
}

void CameraController::moveUp(){
	py -= step;
}

void CameraController::moveDown(){
	py += step;
}


void CameraController::moveBack(){
	pz -= sin(angleX) * step;
	px -= cos(angleX) * step;
	if (pz > constValue) pz = constValue;
	else if (pz < -constValue) pz = -constValue;
	if (px > constValue) px = constValue;
	else if (px < -constValue) px = -constValue;

}
void CameraController::moveLeft(){
	pz -= cos(angleX) * step;
	px += sin(angleX) * step;
	if (pz > constValue) pz = constValue;
	else if (pz < -constValue) pz = -constValue;
	if (px > constValue) px = constValue;
	else if (px < -constValue) px = -constValue;
}

void CameraController::moveRight(){
	pz += cos(angleX) * step;
	px -= sin(angleX) * step;
	if (pz > constValue) pz = constValue;
	else if (pz < -constValue) pz = -constValue;
	if (px > constValue) px = constValue;
	else if (px < -constValue) px = -constValue;
}

Matrix4 CameraController::getRotX(){
	return rotX;
}

Matrix4 CameraController::getRotY(){
	return rotY;
}

Matrix4 CameraController::getTranslation(){
	trans.makeTranslate(px, py, pz);
	return trans;
}

Vector3 CameraController::getPosition(){
	return Vector3(px, py, pz);
}

double CameraController::getAngleX(){
	return angleX;
}

double CameraController::getAngleY(){
	return angleY;
}