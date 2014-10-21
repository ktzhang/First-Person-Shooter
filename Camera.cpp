#include "Camera.h"
#include "math.h"
#include "Vector3.h"

Camera::Camera() {
	upVector = Vector3(0, 0, 0);
	eVector = Vector3(0, 0, 0);
	dVector = Vector3(0, 0, 0);
	for (int i = 0; i < CAMERA_MATRIX*CAMERA_MATRIX; i++) {
		m[i] = 0;
	}
}

double* Camera::getGLMatrix() {
	Vector3 zAxis = eVector - dVector;
	zAxis.normalize();

	Vector3 xAxis = xAxis.cross(upVector, zAxis);
	xAxis.normalize();

	Vector3	yAxis = upVector;
	upVector.normalize();

	for (int i = 0; i < 3; i++) {
		m[i] = xAxis.m[i];
		m[i + 4] = yAxis.m[i];
		m[i + 8] = zAxis.m[i];
		m[i + 12] = this->eVector.m[i];
	}
	m[3] = 0;
	m[7] = 0;
	m[11] = 0;
	m[15] = 1;

	return m;
}