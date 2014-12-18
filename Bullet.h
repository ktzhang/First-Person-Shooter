#ifndef BULLET_H_
#define BULLET_H_

#include "MatrixTransform.h"
#include "Group.h"


class Bullet : public Group{
public:
	Bullet();


	void prerender();
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);

private:
	double radius;
	Vector3 pos;

	MatrixTransform* bullet;
};





#endif