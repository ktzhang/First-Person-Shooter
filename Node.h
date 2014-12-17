#pragma once
#include "Matrix4.h"
#include <vector>

class Node
{
	Node* parent;
public:
	double sphereRadius;
	Vector3 sphereOrigin;
	Node();
	~Node();
	virtual void draw(Matrix4 matrix) = 0;
	virtual void update(Matrix4 matrix) = 0;
	virtual void drawBoundingSpheres(Matrix4 worldMatrix) = 0;
	bool hasParent();
	Node* getParent();
	void setParent(Node* node);
};

