#pragma once
#include "MatrixTransform.h"
#include "Group.h"


class ForestGroup : public Group {
	Group* forest;
	int numTrees;
private:

public:
	ForestGroup();
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	~ForestGroup();
};

