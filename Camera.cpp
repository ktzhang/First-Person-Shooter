#include "Camera.h"
#include "math.h"
#include "Vector3.h"

Camera::Camera() {
	upVector = Vector3(0, 0, 0);
	eVector = Vector3(0, 0, 0);
	dVector = Vector3(0, 0, 0);
	for (int i = 0; i < CAMERA_MATRIX; i++) {
		for (int j = 0; j < CAMERA_MATRIX; j++) {
			m[i][j] = 0;
		}
	}
}


Matrix4* Camera::getGLMatrix() {
	Vector3 zAxis = eVector - dVector;
	zAxis.normalize();

	Vector3 xAxis = xAxis.cross(upVector, zAxis);
	xAxis.normalize();

	Vector3	yAxis = upVector;
	upVector.normalize();

	for (int i = 0; i < 3; i++) {
		m[0][i] = xAxis.m[i];
		m[1][i] = yAxis.m[i];
		m[2][i] = zAxis.m[i];
		m[3][i] = this->eVector.m[i];
	}
	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = 0;
	m[3][3] = 1;
	
	matrix = Matrix4(m);
	return &matrix;
}
