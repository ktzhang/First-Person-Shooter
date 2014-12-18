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
#include "TargetBox.h"
#include "Bullet.h"

extern Reader* reader;



class Window	  // OpenGL output window related routines
{
public:
	static int width, height;
	// window size

	static void init();
	static bool enableMouse;
	static double t;

	static void processNormalKeys(unsigned char key, int x, int y);
	static void processFunctionKeys(int key, int x, int y);

	static void idleCallback(void);
	static void reshapeCallback(int, int);
	static void displayCallback(void);

	static void processMotionFunction(int x, int y);
	static void processMouseFunction(int button, int state, int x, int y);
	static void passiveMouseFunction(int x, int y);

	static void calculateInitialObjectMatrix();

	static void applyGlobalMatrix();
	static void rotateObject(int rotation);
	static void scaleObject(double factor);
	static void rotateObjectX(int rotation);
	static double rd(bool sign = true);

	static void setMaterialType(int type);
	static void displayLights(double x, double y, double z);
	static void displaySpotlight(int x, int y, int z, double angle, Vector3 origin);
	static void spotlightSave();
	static void displaySpotlightCone();

	static void genList();

	//static bool collisionDetected(TargetBox*, Bullet*);
	//static bool collisionDetected2(TargetBox*, Bullet*);
	static Vector3 trackBallMapping(Point point);
};

#endif

