#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Geode.h"
#include "window.h"
#include "Header.h"

class Cube : public Geode
{
	Color color;
	const int CUBE_SIZE = 1;
	public:
		Cube();   // Constructor
		Cube(Color color);
		~Cube(){};
		void Cube::render();
};

#endif

