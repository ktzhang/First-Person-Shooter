#ifndef STRUCTSAHHA
#define STRUCTSAHHA

#include <Windows.h>
#include "GLee.h"
struct Triangle {
	int vector[3];
	int normal[3];
};

struct Color {
	double r;
	double g;
	double b;
};

struct Point {
	int x;
	int y;
};

#endif