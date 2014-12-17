#pragma once
#include "MatrixTransform.h"
#include "Group.h"
#include "Vector3.h"


class EnemyBox : public Group {
private:

public:
	double shrinkFactor = 0.01;
	MatrixTransform* enemy;
	double sidelen;
	Vector3 pos;
	EnemyBox();
	EnemyBox(Vector3 startPos);

	void prerender();
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	~EnemyBox();
};

