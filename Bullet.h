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
private:
	double radius;
	double limit;
	Vector3 pos;
	Vector3 dir;
	Sphere *sphere;
	Cylinder* cylinder;

	int duration;

};





#endif