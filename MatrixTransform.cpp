#include "MatrixTransform.h"
MatrixTransform::MatrixTransform(Matrix4 matrix) {
	setTransformationMatrix(matrix);
}

// Going through each of the groups and drawing the children
void MatrixTransform::draw(Matrix4 worldMatrix) {
	int numberChildren = children.size(); 
	Matrix4 newMatrix = worldMatrix * transformMatrix;
	vector<Node*> children = getChildren();
	for (int i = 0; i < numberChildren; i++) {
		children[i]->draw(newMatrix);
	}
}


void MatrixTransform::update(Matrix4 worldMatrix) {
	int numberChildren = children.size();
	Matrix4 newMatrix = worldMatrix * transformMatrix;
	vector<Node*> children = getChildren();
	for (int i = 0; i < numberChildren; i++) {
		children[i]->update(newMatrix);
	}
}

void MatrixTransform::drawBoundingSpheres(Matrix4 worldMatrix) {
	int numberChildren = children.size();
	Matrix4 newMatrix = worldMatrix * transformMatrix;
	vector<Node*> children = getChildren();
	for (int i = 0; i < numberChildren; i++) {
		children[i]->drawBoundingSpheres(newMatrix);
	}
}

void MatrixTransform::setTransformationMatrix(Matrix4 matrix) {
	transformMatrix = matrix;
}

Matrix4 MatrixTransform::getTransformationMatrix() {
	return transformMatrix;
}

