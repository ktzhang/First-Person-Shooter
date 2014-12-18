#pragma once
#include "MatrixTransform.h"
#include "Group.h"
#include "Vector3.h"


class EnemyBox : public Group {
private:

public:
	double shrinkFactor = 0.01;
	MatrixTransform* enemy;
	double sideLen;
	Vector3 boundingBoxMinMax[2];

	Vector3 moveDirection;
	Vector3 pos;
	double speed;


	EnemyBox();
	EnemyBox(Vector3 startPos, Vector3 direction, double speed);

	void prerender();
	Vector3 newPosition();
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	~EnemyBox();
};

