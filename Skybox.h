#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Skybox : public Geode {
	const int CONE_HEIGHT = 2;
	const int CONE_BASE = 1;
public:
	Skybox() {};
	void render();
	~Skybox() {};
};

#endif