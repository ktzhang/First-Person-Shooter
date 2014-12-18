#ifndef BULLET_H_
#define BULLET_H_

#include "MatrixTransform.h"
#include "Group.h"

#include "Sphere.h"

class Bullet : public Group{

public:
	static const double speed;
	Bullet(Vector3,Vector3);


	void prerender();
	void updateMotion();
	virtual void draw(Matrix4);
	virtual void update(Matrix4);
	virtual void drawBoundingSpheres(Matrix4);

private:
	double radius;
	Vector3 pos;
	Vector3 dir;
	Sphere *sphere;

	MatrixTransform* bullet;
};





#endif