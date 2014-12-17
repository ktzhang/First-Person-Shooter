#ifndef _CYLINDER_H_
#define _CYLINDER_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Cylinder : public Geode {
	double radius;
	double ratioStep;
	double height;
	double ratio;
public:
	Cylinder();
	Cylinder(double height, double radius, double ratio, double ratioStep);
	void render();
	~Cylinder() {};
};

#endif