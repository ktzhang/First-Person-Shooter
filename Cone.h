#ifndef _CONE_H_
#define _CONE_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Cone : public Geode {
	const int CONE_HEIGHT = 2;
	const int CONE_BASE = 1;
public:
	Cone() {};
	void render();
	~Cone() {};
};

#endif