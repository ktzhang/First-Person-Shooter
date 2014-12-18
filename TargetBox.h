#ifndef TARGETBOX_H_
#define TARGETBOX_H_

#include "Geode.h"
#include "Sphere.h"

class TargetBox : public Geode{
public:
	TargetBox(Vector3,Vector3,double);

	virtual void draw(Matrix4);
	virtual void update(Matrix4);
	virtual void drawBoundingSpheres(Matrix4);
	void updatePosition();
	virtual void render();

	Vector3 pos;
	Vector3 dir;

	double limit;
	double scale;
	double speed;

	double px, py, pz;
	double dx, dy, dz;
	Sphere *cube;
};


#endif