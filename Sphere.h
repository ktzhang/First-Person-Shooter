#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Sphere : public Geode {
	const int SPHERE_SIZE = 1;
public:
	Sphere();
	void render();
	~Sphere() {};

	double r, g, b;
};

#endif