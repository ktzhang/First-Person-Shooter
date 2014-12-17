#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

#include "Group.h"
#include "Matrix4.h"

#include <string>

using namespace std;

class MatrixTransform : public Group {
	Matrix4 transformMatrix;
public:

	MatrixTransform(){};
	MatrixTransform(Matrix4 matrix);

	void setTransformationMatrix(Matrix4);
	Matrix4 getTransformationMatrix();
	virtual void draw(Matrix4 worldMatrix);
	virtual void update(Matrix4 worldMatrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
};

#endif