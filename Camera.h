#include <string>
#include "Vector3.h"
#include "Matrix4.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_

#define M_PI 3.14159265358979323846
#define CAMERA_MATRIX 4

class Camera
{
protected:
	Matrix4 matrix;
	double m[CAMERA_MATRIX*CAMERA_MATRIX];   // matrix elements; first index is for rows, second for columns (row-major)
public:
	Camera();
	//Camera(Vector3 upVector, Vector3 eVector, Vector3 dVector);
	Vector3 upVector;
	Vector3 eVector; // Center of projection
	Vector3 dVector; // Look at point
	double* Camera::getGLMatrix();
	double* Camera::getValues();
	
};

#endif