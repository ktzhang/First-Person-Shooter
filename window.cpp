#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <vector>

#include "Group.h"
#include "Geode.h"
#include "Sphere.h"
#include "cube.h"
#include "MatrixTransform.h"
#include "Robot.h"
#include "Skybox.h"
#include "Water.h"
#include "TreeObject.h"

#include <chrono>

using namespace std;
using namespace std::chrono;

const int ROTATE = 0;
const int ZOOM = 1;


int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

extern vector<float> imageNums[2];
extern GLuint p;

extern GLuint texture[6];
Matrix4 finalMatrix;
Matrix4 finalSpotlight;

//Constants
double maxLimbAngle = 25;
int fov = 60;
int cameraDistance = 20;
double imageScale = 0.8;
double nearDistance = 1;
double farDistance = 1000;
int factor = 10;
int size = 30;
int m_ROTSCALE = 5;
double m_ZOOMSCALE = 0.0009;
double spotLightAngle = 10;
int waveEnabled = 1;
//Variables for camera
double zCamera = 0;
double zoomCamera = 1;
int shouldCallUpdate = 1;
int cullingEnabled = 1;
int rotateAngle = 0;
int boundingBoxEnabled = 0;

//Window variables
double windowSize = 0;
double scaleFactor = 0;

//Light variabls
double lightX = 0;
double lightY = 0;
double lightZ = 0;
double spotlightX = 0;
double spotlightY = 1;
double spotlightZ = 0;
double spotlightXPrev = 0;
double spotlightYPrev = 0;
double spotlightZPrev = 0;
Matrix4 spotlightMatrix;
Matrix4 totalRotateSpotlight;
int spotLightEnabled;
Vector3 spotLightDirection;
Vector3 origin;
int enableShaders = 1;
int lightMotionEnabled = 0;
int rayModelEnabled = 0;

int enablePointLight = 1;
int enableMultiWave = 0;
//Material Variables
int materialType = 1;

Vector3 planes[12];

Reader* bunny;
Reader* dragon;
Reader* bear;
Reader* reader;

//Wave Stuff
double increment1 = 0.0;
double increment2 = 0.0;
double increment3 = 3.19* M_PI / 2;
double increment4 = 3.19* M_PI / 2;


double waveOffset = 0.0;


void Window::init() {
	bunny = new Reader("bunny.obj");
	dragon = new Reader("dragon.obj", Color{ 0.9, 0.9, 0.3 });
	bear = new Reader("bear.obj");
	reader = bunny;

	finalMatrix.identity();
	finalSpotlight.identity();
	spotlightMatrix.identity();
	totalRotateSpotlight.identity();
	origin = Vector3(0, 0, 0);
}

//----------------------------------------------------------------------------
// Callback method of keyboard input
void Window::processNormalKeys(unsigned char key, int x, int y)
{
	cout << "          |" << key << " pressed!";
	shouldCallUpdate = 1;
	switch (key) {
		//'t' for spinning clockwise or counter clockwise
	case 'c':
		cullingEnabled = !cullingEnabled;
		break;

	case 'b':
		enableShaders = !enableShaders;
		break;
	case 'a':
		lightX += 1;
		break;

	case 'A':
		lightX -= 1;
		break;

	case 's':
		lightY += 1;
		break;
		// 'X' right
	case 'S':
		lightY -= 1;
		break;
		//'x' left 
	case 'd':
		lightY += 1;
		break;
		// 'X' right
	case 'D':
		lightY -= 1;
		break;

	case 'w':
		//spotlightSave();
		waveEnabled = !waveEnabled;

		break;
	case 'W':
		//spotlightSave();
		spotlightY -= 1;
		displaySpotlightCone();

		break;
	case 'q':
		//spotlightSave();
		spotlightX += 1;
		displaySpotlightCone();

		break;
	case 'Q':
		//spotlightSave();
		spotlightX -= 1;
		displaySpotlightCone();

		break;
	case 'e':
		rotateObjectX(20);
		break;
	case 'E':
		rotateObjectX(-20);


		break;

	case 'l':
		lightMotionEnabled = 1;
		cout << "\nLightMotionEnabled = " << lightMotionEnabled;
		break;
	case 'm':
		enableMultiWave = !enableMultiWave;
		/*	lightMotionEnabled = 0;
		cout << "\nLightMotionEnabled = " << lightMotionEnabled;*/
		break;
		// 'y' down 
	case 121:
		zCamera += 1;
		break;

		// 'Y' up
	case 89:
		zCamera -= 1;
		break;


	case 'h':
		waveOffset += 0.1;
		break;

	case 'H':
		waveOffset -= 0.1;
		break;
		// 'z' in
	case 122:
		//imageScale *= 0.8;
		scaleObject(0.8);
		break;

		// 'Z' out
	case 90:
		//imageScale *= 1 / 0.8;
		scaleObject(1 / 0.8);
		break;

	case 'k':
		rayModelEnabled = !rayModelEnabled;
		cout << "\nRay Model Enabled = " << rayModelEnabled;
		break;
	case ';':
		if (materialType == 4) {
			materialType = 1;
		}
		else {
			materialType++;
		}
		cout << " \nMaterial Type = " << materialType;
		break;
		// 'r' reset
	case 114:
		break;

		// 'o' orbit counterclockwise
	case 'X':
		rotateObject(20);
		break;

		// 'O' orbit clockwise
	case 'x':
		rotateObject(-20);
		break;


	case 'p':
		enablePointLight = !enablePointLight;
		cout << "\nShaders enabled: " << enableShaders;

		break;
	}

}

void Window::spotlightSave() {
	spotlightXPrev = spotlightX;
	spotlightYPrev = spotlightY;
	spotlightZPrev = spotlightZ;
}

void Window::scaleObject(double factor) {
	Matrix4 scale;
	scale.makeScale(factor, factor, factor);
	finalMatrix = finalMatrix * scale;

}

void Window::rotateObject(int rotation) {
	Matrix4 rotate;
	rotate.makeRotateY(rotation);

	//Storing to final Matrix
	finalMatrix = finalMatrix * rotate;
	displayCallback();
}

void Window::rotateObjectX(int rotation) {
	Matrix4 rotate;
	rotate.makeRotateX(rotation);

	//Storing to final Matrix
	finalMatrix = finalMatrix * rotate;
	displayCallback();

}

void Window::processFunctionKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		reader = bunny;
	}
	else if (key == GLUT_KEY_F2) {
		reader = dragon;
	}
	else if (key == GLUT_KEY_F3) {
		reader = bear;
	}
	else if (key == GLUT_KEY_F4) {
		//viewMode = 4;
	}
	else if (key == GLUT_KEY_F5) {
		//viewMode = 3;
	}
	calculateInitialObjectMatrix();

}



//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	displayCallback();         // call display routine to show the cube
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	double durationDouble = duration / 1000000;
	//cout << "FPS = " << (1/durationDouble) << " ";

}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, double(width) / (double)height, nearDistance, farDistance); // set perspective projection viewing frustum
	//glTranslatef(0, 0, -cameraDistance);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -5);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)

	glMatrixMode(GL_MODELVIEW);
	windowSize = (cameraDistance * tan(((fov / 2) / 180.0) * M_PI)) * 2;
	calculateInitialObjectMatrix();
	waveOffset = 0;
	genList();
}

struct CameraVectors {
	Vector3 centerVector;
	Vector3 dVector;
	Vector3 upVector;
};

void calculatePlanes(Camera camera) {
	Vector3 dVectorDirection = camera.dVector - camera.eVector;
	dVectorDirection.normalize();

	//Near Plane
	Vector3 scaledVectorNear = dVectorDirection;
	scaledVectorNear.normalize();
	scaledVectorNear.scale(nearDistance);
	Vector3 nearPoint = camera.eVector + scaledVectorNear;
	Vector3 nearVectorDirection = dVectorDirection;
	nearVectorDirection.scale(-1);
	nearVectorDirection.normalize();

	//Far Plane
	Vector3 scaledVectorFar = dVectorDirection;
	scaledVectorFar.normalize();
	scaledVectorFar.scale(farDistance);
	Vector3 farPoint = camera.eVector + scaledVectorFar;
	Vector3 farVectorDirection = dVectorDirection;
	farVectorDirection.normalize();


	//Calculating widths of stuff
	double nearSize = (nearDistance * tan(((fov / 2) / 180.0) * M_PI)) * 2;
	double farSize = (farDistance * tan(((fov / 2) / 180.0) * M_PI)) * 2;

	//Right Plane 
	Vector3 rightVector = Vector3();
	rightVector = rightVector.cross(dVectorDirection, camera.upVector);
	rightVector.normalize();

	rightVector.scale(nearSize / 2);
	Vector3 temp = (nearPoint + rightVector);
	Vector3 aDirection = temp - camera.eVector;
	aDirection.normalize();
	Vector3 rightPlaneNormal = Vector3();
	rightPlaneNormal = rightPlaneNormal.cross(aDirection, camera.upVector);
	rightPlaneNormal.normalize();

	//Left Plane
	Vector3 leftVector = Vector3();
	leftVector = leftVector.cross(camera.upVector, dVectorDirection);
	leftVector.normalize();

	leftVector.scale(nearSize / 2);
	Vector3 bDirection = (nearPoint + leftVector) - camera.eVector;
	bDirection.normalize();
	Vector3 leftPlaneNormal = Vector3();
	leftPlaneNormal = leftPlaneNormal.cross(camera.upVector, bDirection);
	leftPlaneNormal.normalize();

	Vector3 leftVectorNew = Vector3();
	leftVectorNew = leftVectorNew.cross(camera.upVector, dVectorDirection);
	leftVectorNew.normalize();

	//Top Plane
	Vector3 topVector = camera.upVector;
	topVector.normalize();

	topVector.scale(nearSize / 2);
	Vector3 tDirection = (nearPoint + topVector) - camera.eVector;
	tDirection.normalize();
	Vector3 topPlaneNormal = Vector3();
	topPlaneNormal = topPlaneNormal.cross(tDirection, leftVectorNew);
	topPlaneNormal.normalize();

	//bottom Plane
	Vector3 bottomVector = camera.upVector;
	bottomVector.scale(-1);
	bottomVector.normalize();

	bottomVector.scale(nearSize / 2);
	Vector3 botDirection = (nearPoint + bottomVector) - camera.eVector;
	botDirection.normalize();
	Vector3 bottomPlaneNormal = Vector3();
	bottomPlaneNormal = bottomPlaneNormal.cross(leftVectorNew, botDirection);
	bottomPlaneNormal.normalize();


	planes[0] = nearPoint;
	planes[1] = nearVectorDirection;
	planes[2] = farPoint;
	planes[3] = farVectorDirection;
	planes[4] = camera.eVector;
	planes[5] = rightPlaneNormal;
	planes[6] = camera.eVector;
	planes[7] = leftPlaneNormal;
	planes[8] = camera.eVector;
	planes[9] = topPlaneNormal;
	planes[10] = camera.eVector;
	planes[11] = bottomPlaneNormal;

}


TreeObject *treeObj;
void Window::genList() {
	treeObj = new TreeObject(5, 3.0, 25, 1.0);
	treeObj->setAxiom("F");
	//treeObj.addRule('F', "FFF", 1);
	//treeObj->addRule('F', "FF-[-F+F]+[+F-F]", 1);
	//treeObj->addRule('X', "FF+[+F]+[-F]", 1);
	treeObj->addRule('F', "F [- & < F][ < + + & F ] | | F [ - - & > F ] [+&F]", 1);
	treeObj->prerender();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	//cerr << "display callback" << endl;

	double incAmount = 0.02;
	double offset = 0.495;

	setMaterialType(3);
	/* clear the color buffer (resets everything to black) */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Group world = Group();
	MatrixTransform objTrans = MatrixTransform(finalMatrix);
	world.addChild(&objTrans);
	objTrans.addChild(treeObj);


	Skybox sky = Skybox();
	objTrans.addChild(&sky);


	Group bottom = Group();
	objTrans.addChild(&bottom);


	Matrix4 water1MatS = Matrix4();
	water1MatS.makeScale(.5, .5, .5);
	Matrix4 water1MatT = Matrix4();
	water1MatT.makeTranslate(offset, 0.1 + waveOffset, offset);
	Matrix4 water1Mat;
	water1Mat.identity();
	if (enableMultiWave) {
		water1Mat = water1MatT * water1MatS;
	}
	else {
		water1MatT.identity();
		water1MatT.makeTranslate(0, 0.1 + waveOffset, 0);
		water1Mat = water1MatT;
	}
	MatrixTransform water1T = MatrixTransform(water1Mat);
	Water water = Water();
	increment1 += incAmount;
	water.initialize(increment1, waveEnabled);
	water1T.addChild(&water);
	bottom.addChild(&water1T);



	Matrix4 water2MatS = Matrix4();
	water2MatS.makeScale(.5, .5, .5);
	Matrix4 water2MatT = Matrix4();
	water2MatT.makeTranslate(-offset, 0.1 + waveOffset, offset);
	Matrix4 water2Mat;
	water2Mat.identity();
	water2Mat = water2MatT * water2MatS;
	MatrixTransform water2T = MatrixTransform(water2Mat);
	Water water2 = Water();
	increment2 += incAmount;
	if (enableMultiWave) {
		water2.initialize(increment2, waveEnabled);
		water2T.addChild(&water2);
		bottom.addChild(&water2T);
	}

	Matrix4 water3MatS = Matrix4();
	water3MatS.makeScale(.5, .5, .5);
	Matrix4 water3MatT = Matrix4();
	water3MatT.makeTranslate(offset, 0.1 + waveOffset, -offset);
	Matrix4 water3Mat;
	water3Mat.identity();
	water3Mat = water3MatT * water3MatS;
	MatrixTransform water3T = MatrixTransform(water3Mat);
	Water water3 = Water();
	increment3 += incAmount;
	if (enableMultiWave) {
		water3.initialize(increment3, waveEnabled);
		water3T.addChild(&water3);
		bottom.addChild(&water3T);
	}

	Matrix4 water4MatS = Matrix4();
	water4MatS.makeScale(.5, .5, .5);
	Matrix4 water4MatT = Matrix4();
	water4MatT.makeTranslate(-offset, 0.1 + waveOffset, -offset);
	Matrix4 water4Mat;
	water4Mat.identity();
	water4Mat = water4MatT * water4MatS;
	MatrixTransform water4T = MatrixTransform(water4Mat);
	Water water4 = Water();
	increment4 += incAmount;
	if (enableMultiWave) {
		water4.initialize(increment4, waveEnabled);
		water4T.addChild(&water4);
		bottom.addChild(&water4T);
	}




	Matrix4 identity = Matrix4();
	identity.identity();

	//Drawing world

	//Point light source
	Matrix4 pointLightMatrix = Matrix4();
	pointLightMatrix.makeTranslate(lightX, lightY, lightZ);
	displayLights(lightX, lightY, lightZ);
	MatrixTransform pointLightTrans = MatrixTransform(pointLightMatrix);
	Sphere pointLightSphere = Sphere();
	pointLightTrans.addChild(&pointLightSphere);
	if (enablePointLight)
		world.addChild(&pointLightTrans);

	world.draw(identity);

	/* swap the back and front buffers so we can see what we just drew */
	glutSwapBuffers();
	glFlush();
}

void Window::displaySpotlightCone() {
	// Calculate base path
	spotlightXPrev = origin.m[0];
	spotlightYPrev = origin.m[1];
	spotlightZPrev = windowSize / 2.2;
	//spotlightSave();
	//Spotlight source
	Matrix4 spotLightMatrixTrans = Matrix4();
	spotLightMatrixTrans.makeTranslate(spotlightX - spotlightXPrev, spotlightY - spotlightYPrev, spotlightZ - spotlightZPrev);

	//Given a direction pointed -> want to rotate cone to point in the direction

	Vector3 spotLightPositionOld = Vector3(spotlightXPrev, spotlightYPrev, spotlightZPrev);
	Vector3 spotLightPositionNew = Vector3(spotlightX, spotlightY, spotlightZ);

	//Given a point in x, y, z -> want to rotate the cone so that it faces x, y, z
	Vector3 spotLightDirectionOld = origin - spotLightPositionOld;
	spotLightDirectionOld.normalize();
	Vector3 spotLightDirectionNew = origin - spotLightPositionNew;
	spotLightDirectionNew.normalize();
	spotLightDirection = spotLightDirectionNew;

	Vector3 axis = axis.cross(spotLightDirectionNew, spotLightDirectionOld);
	axis.normalize();

	double spotlightRotateAngle = spotLightDirectionOld.angleBetween(spotLightDirectionOld, spotLightDirectionNew);

	Matrix4 rotateSpotlight = Matrix4();
	rotateSpotlight.makeRotate(spotlightRotateAngle, axis);

	totalRotateSpotlight = rotateSpotlight;
	finalSpotlight = spotLightMatrixTrans * totalRotateSpotlight;
}

void Window::setMaterialType(int type) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0 };
	GLfloat low_shininess[] = { 5.0 };
	GLfloat high_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };
	switch (type) {
	case 1:
		// Generate material properties:
		Material::setAmbient(no_mat);
		Material::setDiffuse(mat_diffuse);
		Material::setSpecular(no_mat);
		Material::setShininess(no_shininess);
		Material::setEmission(no_mat);
		break;
	case 2:
		Material::setAmbient(no_mat);
		Material::setDiffuse(no_mat);
		Material::setSpecular(mat_specular);
		Material::setShininess(high_shininess);
		Material::setEmission(no_mat);
		break;
	case 3:
		Material::setAmbient(no_mat);
		Material::setDiffuse(mat_diffuse);
		Material::setSpecular(mat_specular);
		Material::setShininess(low_shininess);
		Material::setEmission(no_mat);
		break;
	case 4:
	case 0:
		Material::setAmbient(no_mat);
		Material::setDiffuse(mat_diffuse);
		Material::setSpecular(no_mat);
		Material::setShininess(no_mat);
		Material::setEmission(mat_emission);
		break;
	}
}

void Window::displayLights(double x, double y, double z) {
	Matrix4 identity = Matrix4();
	identity.identity();
	glLoadMatrixd(identity.getPointer());
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { x, y, z, 1.0 };
	Light light = Light(GL_LIGHT1);
	light.setConstantAttenuation(0.5);
	light.setLinearAttenuation(0.1);
	light.setDiffuse(light_diffuse);
	light.setAmbient(light_ambient);
	light.setSpecular(light_specular);
	light.setPosition(light_position);
	light.enable();
}

void Window::displaySpotlight(int x, int y, int z, double angle, Vector3 origin) {


	//glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


	//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);

	//glEnable(GL_LIGHT1);
	Vector3 position = Vector3(x, y, z);
	Vector3 direction = origin - position;

	Matrix4 identity = Matrix4();
	identity.identity();
	glLoadMatrixd(identity.getPointer());
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { x, y, z, 1.0 };
	Light light = Light(GL_LIGHT0);
	light.setConstantAttenuation(0.5);
	light.setLinearAttenuation(0.1);
	light.setCutoff(angle);
	light.setSpotDirection(direction);
	light.setDiffuse(light1_diffuse);
	light.setAmbient(light1_ambient);
	light.setSpecular(light1_specular);
	light.setPosition(light_position);
	light.setExponent(2.0);
	light.enable();
}

void Window::calculateInitialObjectMatrix() {
	Matrix4 zoom;
	zoom.identity();
	zoom.makeScale(3, 3, 3);
	Matrix4 rotate;
	rotate.identity();
	rotate.makeRotateX(-30);

	finalMatrix.identity();
	finalMatrix = finalMatrix * rotate * zoom;
}

void Window::rayModelCalc(int x, int y) {
	//1 convert from window coords to world coords
	/*windowSize;*/
	double percentX = (double)x / (double)glutGet(GLUT_WINDOW_WIDTH);
	double percentY = (double)y / (double)glutGet(GLUT_WINDOW_HEIGHT);
	double actualX = (double)windowSize * percentX;
	double actualY = (double)windowSize * percentY;

	Vector3 p = Vector3(actualX - windowSize / 2, actualY - windowSize / 2, 0);
	Vector3 d = Vector3(0, 0, 1);

	vector<Vector3> posVectors = reader->getPosVectors();
	vector<Triangle> triangleVectors = reader->getTriangles();
	int iVector0, iVector1, iVector2, touches;
	for (std::vector<int>::size_type i = 0; i != triangleVectors.size(); i++) {
		iVector0 = triangleVectors[i].vector[0] - 1;
		iVector1 = triangleVectors[i].vector[1] - 1;
		iVector2 = triangleVectors[i].vector[2] - 1;
		Vector4 posX = { posVectors[iVector0].m[0], posVectors[iVector0].m[1], posVectors[iVector0].m[2], 1 };
		Vector4 posY = { posVectors[iVector1].m[0], posVectors[iVector1].m[1], posVectors[iVector2].m[2], 1 };
		Vector4 posZ = { posVectors[iVector2].m[0], posVectors[iVector2].m[1], posVectors[iVector2].m[2], 1 };

		posX = finalMatrix * posX;
		posY = finalMatrix * posY;
		posZ = finalMatrix * posZ;

		Vector3 posXNew = Vector3(posX.m[0], posX.m[1], posX.m[2]);

		Vector3 posYNew = Vector3(posY.m[0], posY.m[1], posY.m[2]);

		Vector3 posZNew = Vector3(posZ.m[0], posZ.m[1], posZ.m[2]);

		touches = rayIntersectsTriangle(p, d, posXNew, posYNew, posZNew);
		if (touches) {
			//cout << "YESSSSSSSSSSSSSSSSSSS I TOUCHED";
		}
	}
}


int Window::rayIntersectsTriangle(Vector3 p, Vector3 d, Vector3 v0, Vector3 v1, Vector3 v2) {
	Vector3 e1, e2, h, s, q;
	float a, f, u, v;
	e1 = v1 - v0;
	e2 = v2 - v0;

	h = h.cross(d, e2);
	a = e1.dot(e1, h);

	if (a > -0.00001 && a < 0.00001)
		return(false);

	f = 1 / a;
	s = p - v0;
	u = f * (s.dot(s, h));

	if (u < 0.0 || u > 1.0)
		return(false);

	q = q.cross(s, e1);
	v = f * d.dot(d, q);

	if (v < 0.0 || u + v > 1.0)
		return(false);

	// at this stage we can compute t to find out where
	// the intersection point is on the line
	float t = f * e2.dot(e2, q);

	if (t > 0.00001) {// ray intersection
		cout << "\nTX: " << t << " TY: " << u << " TZ: " << v;
		origin = Vector3(p.m[0], p.m[1], t);
		displaySpotlightCone();
		return(true);
	}

	else // this means that there is a line intersection
		// but not a ray intersection
		return (false);
}

void Window::applyGlobalMatrix() {
	glLoadMatrixd(finalMatrix.getPointer());
}

Vector3 lastPoint;
int Movement;

void Window::processMouseFunction(int button, int state, int x, int y) {
	Point point = Point{ x, y };
	switch (button) {
	case 0:
		Movement = ROTATE;
		lastPoint = trackBallMapping(point);
		if (rayModelEnabled && state == 0) {
			rayModelCalc(x, y);
		}
		break;
	case 2:
		Movement = ZOOM;
		lastPoint = Vector3(point.x, point.y, 0);
		break;
	}
	cout << "\n state" << state << " button" << button << " x" << x << " y" << y;
}

Vector3 Window::trackBallMapping(Point point) {
	Vector3 v;
	float d;
	v.m[0] = (2.0 * point.x - width) / width;
	v.m[1] = (height - 2.0*point.y) / height;
	v.m[2] = 0.0;
	d = v.length();
	d = (d < 1.0) ? d : 1.0;
	v.m[2] = sqrtf(1.001 - d*d);
	v.normalize(); // Still need to normalize, since we only capped d, not v.
	return v;
}

void Window::processMotionFunction(int x, int y) {
	cout << "\n" << "x" << x << " y" << y;
	Point point = Point{ x, y };
	//Detect mouse movement:
	Vector3 direction;
	float pixel_diff, pixel_diffY;
	float rot_angle, zoom_factor, zoom_factorY;
	Vector3 curPoint;
	switch (Movement)
	{

	case ROTATE: // Left-mouse button is being held down
	{
		curPoint = trackBallMapping(point); // Map the mouse position to a logical
		// sphere location.
		direction = curPoint - lastPoint;
		float velocity = direction.length();
		cout << " v: " << velocity;
		if (velocity > 0.0001) // If little movement - do nothing.
		{
			//
			// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
			//
			if (!lightMotionEnabled) {
				Vector3 rotAxis;
				rotAxis = rotAxis.cross(lastPoint, curPoint);
				rotAxis.normalize();
				rot_angle = velocity * m_ROTSCALE;
				//
				// We need to apply the rotation as the last transformation.
				// 1. Get the current matrix and save it.
				// 2. Set the matrix to the identity matrix (clear it).
				// 3. Apply the trackball rotation.
				// 4. Pre-multiply it by the saved matrix.
				//
				/*GLdouble modelMatrix[16];
				glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
				Matrix4 objectXform = Matrix4(modelMatrix);
				glLoadIdentity();*/

				Matrix4 rotateMatrix = Matrix4();
				rotateMatrix.identity();
				rotateMatrix.makeRotate(-rot_angle, rotAxis);
				//glRotated(rot_angle, rotAxis.m[0], rotAxis.m[1], rotAxis.m[2]);

				finalMatrix = rotateMatrix * finalMatrix;
			}
			else {
				spotlightX = curPoint.m[0] * 10;
				spotlightY = curPoint.m[1] * 10;
				spotlightZ = 12 + curPoint.m[2] * 5;
				displaySpotlightCone();
			}

			//glMultMatrixd(objectXform.getPointer());
		}
		break;
	}
	case ZOOM: // Right-mouse button is being held down
		//
		// Zoom into or away from the scene based upon how far the 
		// mouse moved in the x-direction.
		// This implementation does this by scaling the eye-space.
		// This should be the first operation performed by the GL_PROJECTION matrix.
		// 1. Calculate the signed distance
		// a. movement to the left is negative (zoom out).
		// b. movement to the right is positive (zoom in).
		// 2. Calculate a scale factor for the scene s = 1 + a*dx
		// 3. Call glScalef to have the scale be the first transformation.
		//
		if (!lightMotionEnabled) {
			pixel_diff = point.x - lastPoint.m[0];
			zoom_factor = 1.0 + pixel_diff * m_ZOOMSCALE;
			scaleObject(zoom_factor);
		}
		else {
			pixel_diffY = point.y - lastPoint.m[1];
			zoom_factorY = 1.0 + pixel_diffY * m_ZOOMSCALE * 1.5;
			spotLightAngle *= zoom_factorY;
			displaySpotlightCone();
		}
		//
		// Set the current point, so the lastPoint will be saved properly below . 
		// 
		lastPoint.m[0] = point.x;
		lastPoint.m[1] = point.y;
		lastPoint.m[2] = 0;

		break;
	}

	displayCallback();

}



