#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Skybox : public Geode {
public:
	static const double SIDELEN;
	Skybox() {};
	void render();
	//void prerender();
	~Skybox() {};
};

#endif