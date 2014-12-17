#ifndef _WATER_H_
#define _WATER_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Water : public Geode {
	Vector3 anchors[4][4];

public:
	Water() {};
	void render();
	~Water() {};
	void initialize(double increment, int on);
};

#endif