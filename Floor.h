#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "Geode.h"
#include "Matrix4.h"

using namespace std;

class Floor : public Geode {
	int numSquares;

public:
	Floor() {
		numSquares = 10;
	};
	void render();
	~Floor() {};
};

#endif