#ifndef BULLET_H_
#define BULLET_H_

#include "MatrixTransform.h"
#include "Geode.h"

#include "Cylinder.h"
#include "Sphere.h"

class Bullet : public Geode{

public:
	static const double speed;
	Bullet(Vector3,Vector3,double);


	void updateMotion();
	virtual void draw(Matrix4);
	virtual void update(Matrix4);
	virtual void drawBoundingSpheres(Matrix4);
	virtual void render();

	int getDuration();
	Vector3 pos;
	Vector3 dir;
	double radius;
private:
	double limit;
	Sphere *sphere;
	Cylinder* cylinder;

	int duration;

};





#endif