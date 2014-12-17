#ifndef _WINDOW_H_
#define _WINDOW_H_


#include "Header.h"
#include "Reader.h"
#include "Matrix4.h"
#include "Light.h"
#include "MatrixTransform.h"
#include "Geode.h"
#include "Material.h"
#include "Cone.h"

extern Reader* reader;



class Window	  // OpenGL output window related routines
{
public:
	static int width, height;
	// window size

	static void init();

	static void processNormalKeys(unsigned char key, int x, int y);
	static void processFunctionKeys(int key, int x, int y);

	static void idleCallback(void);
	static void reshapeCallback(int, int);
	static void displayCallback(void);

	static void processMotionFunction(int x, int y);
	static void processMouseFunction(int button, int state, int x, int y);


	static void calculateInitialObjectMatrix();

	static void applyGlobalMatrix();
	static void rotateObject(int rotation);
	static void scaleObject(double factor);
	static void rotateObjectX(int rotation);


	static void setMaterialType(int type);
	static void displayLights(double x, double y, double z);
	static void displaySpotlight(int x, int y, int z, double angle, Vector3 origin);
	static void spotlightSave();
	static void displaySpotlightCone();

	static void rayModelCalc(int x, int y);
	static int rayIntersectsTriangle(Vector3 p, Vector3 d,
		Vector3 v0, Vector3 v1, Vector3 v2);

	static void genList();

	static Vector3 trackBallMapping(Point point);
};

#endif

