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
#include "Floor.h"
#include "ForestGroup.h"
#include "EnemyBox.h"
#include "CamControl.h"
#include <chrono>
#include "Bullet.h"
#include "ParticleEffect.h"
#include "TargetBox.h"

using namespace std;
using namespace std::chrono;

const int ROTATE = 0;
const int ZOOM = 1;

double Window::t = 1.0;

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
bool Window::enableMouse = true;

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
double nearDistance = 0.5;
double farDistance = 1000;
int factor = 10;
int size = 30;
int m_ROTSCALE = 5;
double m_ZOOMSCALE = 0.0009;
double spotLightAngle = 10;
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

CameraController *camera;
Matrix4 cameraMatrix;
vector<Bullet*> *bullets;
vector<TargetBox*> *boxes;
vector<ParticleEffect*> *effects;
bool addBullet = false;

std::vector<EnemyBox>* enemies = new vector<EnemyBox>();

void Window::init() {
	/*bunny = new Reader("bunny.obj");
	dragon = new Reader("dragon.obj", Color{ 0.9, 0.9, 0.3 });
	bear = new Reader("bear.obj");
	reader = bunny;*/

	//finalMatrix.identity();
	//finalSpotlight.identity();
	//spotlightMatrix.identity();
	//totalRotateSpotlight.identity();
	//origin = Vector3(0, 0, 0);

	camera = new CameraController();
	cameraMatrix.identity();
	bullets = new vector<Bullet*>();
	effects = new vector<ParticleEffect*>();

	boxes = new vector<TargetBox*>();
	TargetBox *box = new TargetBox(Vector3(0.12, 0.1, 0.2), Vector3(0, 0, 0),0.02,1);
	boxes->push_back(box);

	for (int i = 0; i < 4; i++){
		box = new TargetBox(Vector3(rd(), rd(false), rd()), Vector3(1, 0, 0),0.03,1);
		boxes->push_back(box);
	}
	for (int i = 0; i < 4; i++){
		box = new TargetBox(Vector3(rd(), rd(false), rd()), Vector3(0, 1, 0), 0.03, 1);
		boxes->push_back(box);
	}
	for (int i = 0; i < 4; i++){
		box = new TargetBox(Vector3(rd(), rd(false), rd()), Vector3(0, 0, 1), 0.03, 1);
		boxes->push_back(box);
	}
	for (int i = 0; i < 6; i++){
		box = new TargetBox(Vector3(rd(), rd(false), rd()), Vector3(0, 0, 0),0.02, 1);
		boxes->push_back(box);
	}

}

double Window::rd(bool sign){
	double r = rand() % 1000;
	double s = 1;
	if(sign) s = 2 * (rand() % 2) - 1;
	return s * r / 1000;
}
//----------------------------------------------------------------------------
// Callback method of keyboard input
void Window::processNormalKeys(unsigned char key, int x, int y)
{
//	cout << "          |" << key << " pressed!";
	shouldCallUpdate = 1;
	switch (key) {
	case 'a':
		camera->moveLeft();
		cameraMatrix = camera->getTranslation();
		break;
	case 's':
		camera->moveBack();
		cameraMatrix = camera->getTranslation();
		break;
	case 'd':
		camera->moveRight();
		cameraMatrix = camera->getTranslation();
		break;
	case 'w':
		camera->moveForward();
		cameraMatrix = camera->getTranslation();
		break;
	case 'e':
		camera->moveUp();
		cameraMatrix = camera->getTranslation();
		break;
	case 'q':
		camera->moveDown();
		cameraMatrix = camera->getTranslation();
		break;
	case 'm':
		enableMouse = !enableMouse;
		break;
	case 'g':
		genList();
		break;
	}
	//Vector3 vec = camera->getPosition();
	//cout << "Camera position: x=" << vec.m[0] << "  y=" << vec.m[1] << "  z=" << vec.m[2] << endl;
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



EnemyBox enemyBox;
//TODO move enemybox to init
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
	glTranslatef(0, 0, 0);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)

	glMatrixMode(GL_MODELVIEW);
	windowSize = (cameraDistance * tan(((fov / 2) / 180.0) * M_PI)) * 2;
	calculateInitialObjectMatrix();
	genList();
}

struct CameraVectors {
	Vector3 centerVector;
	Vector3 dVector;
	Vector3 upVector;
};

TreeObject *treeObj[10];
ForestGroup *forestGroup;
double forestX[10];
double forestY[10];


void Window::genList() {
	char symbolList[6] = { 'F', '+', '-', '&', '<', 'I' };
	int randNum;
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		treeObj[i] = new TreeObject(2, 4.0, 20, 1.0);
		char ax[7];
		randNum = (rand() % (1 - 0)) + 0;
		if (randNum)
			ax[0] = 'F';
		else
			ax[0] = 'I';
		for (int j = 0; j < 6; j++) {
			randNum = (rand() % (5 - 0)) + 0;
			ax[j+1] = symbolList[randNum];
		}
		string str(ax);
		treeObj[i]->setAxiom(str);
		//treeObj[i].addRule('F', "FFF", 1);
		//treeObj[i]->addRule('F', "FF-[-F+F]+[+F-F]", 1);
		//treeObj[i]->addRule('X', "FF+[+F]+[-F]", 1);
		treeObj[i]->addRule('F', "F-[C1-<F+F&F+F+F]+[C2+F-<F+F&F]", 1);
		treeObj[i]->addRule('X', "X [- X&X < X][ X< X+ X+ X& X]", 1);
		treeObj[i]->addRule('I', "C0FF<[C1+F]+[C3-F]", 1);
		treeObj[i]->prerender();
	}
	double randX, randY;

	for (int i = 0; i < 10; i++) {
		randX = ((double)rand() / (RAND_MAX));
		randY = ((double)rand() / (RAND_MAX));
		forestX[i] = randX * 1.8 - .9;
		forestY[i] = randY * 1.8 - .9;
	}
	forestGroup = new ForestGroup();
	forestGroup->prerender();

	/*
	int initialEnemies = 3;
	Vector3 singleEnemyPos;
	double x, y, z, enemyBorderSize, enemyBorderFactor;
	for (int i = 0; i < initialEnemies; i++) {
		EnemyBox singleEnemy = EnemyBox();
		enemyBorderSize = singleEnemy.sideLen;
		enemyBorderFactor = (Skybox::SIDELEN - enemyBorderSize);
		x = ((double)rand() / (RAND_MAX)) * enemyBorderFactor - Skybox::SIDELEN/2;
		y = ((double)rand() / (RAND_MAX)) * enemyBorderFactor;
		z = ((double)rand() / (RAND_MAX)) * enemyBorderFactor - Skybox::SIDELEN/2;
		cout << "x, y, z" << x << " " << y << " " << z;
		singleEnemyPos = Vector3(x, y, z);
		singleEnemy.pos = singleEnemyPos;
		singleEnemy.speed = 0.005;
		enemies->push_back(singleEnemy);
	}

	enemyBox = EnemyBox(Vector3(-0.5, 0, -0.5), Vector3(1, 0, 0), 0.005);

	*/

}
//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	setMaterialType(3);
	/* clear the color buffer (resets everything to black) */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Target boxes
	vector<TargetBox*>::iterator tb;
	for (tb = boxes->begin(); tb != boxes->end(); tb++){
		TargetBox *box = *tb;
		box->draw(finalMatrix * cameraMatrix);
		box->drawBoundingSpheres(finalMatrix * cameraMatrix);
	}

	//Bullets!
	vector<Bullet*>::iterator bu;
	int ct = 0;
	for (bu = bullets->begin(); bu != bullets->end(); bu++){
		Bullet * bullet = *bu;
		bullet->draw(finalMatrix * cameraMatrix);
		if (bullet->getDuration() > 0){
			ct++;
			for (int i = 0; i < boxes->size(); i++){
				if(collisionDetected(boxes->at(i),bullet)){
					//cout << "HITTTT!" << endl;
					ParticleEffect *effect = new ParticleEffect(boxes->at(i)->pos);
					effects->push_back(effect);
					boxes->erase(boxes->begin() + i);
					break;
				}
			}
		}
	}
	if (ct == 0){
		bullets->clear();
	}

	ct = 0;
	vector<ParticleEffect*>::iterator pa;
	for (pa = effects->begin(); pa != effects->end(); pa++){
		ParticleEffect *effect = *pa;
		effect->draw(finalMatrix * cameraMatrix);
		if (effect->alive){
			ct++;
		}
	}
	if (ct == 0) effects->clear();

	
	Group world = Group();
	MatrixTransform objTrans = MatrixTransform(finalMatrix*cameraMatrix);
	world.addChild(&objTrans);


	//double treeShrinkFactor = 0.0005;
	//Matrix4 treeShrinkMatrix;
	//treeShrinkMatrix.identity();
	//treeShrinkMatrix.makeScale(treeShrinkFactor, treeShrinkFactor, treeShrinkFactor);
	//MatrixTransform treeTrans = MatrixTransform(treeShrinkMatrix);
	//treeTrans.addChild(treeObj);
	//objTrans.addChild(&treeTrans);

	//ForestGroup treeForest;



	//Matrix4 parMat;
	//parMat.makeTranslate(-0.15, 0.0, -0.2);
	//MatrixTransform parTrans = MatrixTransform(parMat);
	//parTrans.addChild(particles);
	//objTrans.addChild(&parTrans);


	//vector<Bullet>::iterator it;
	//stack<int> stack;
	//for (it = bullets->begin(); it != bullets->end(); it++){

	//}



	//if (addBullet){
	//	Bullet *bullet = new Bullet(Vector3(0,0,0),Vector3(0,0,-1));
	//	Matrix4 iden;
	//	iden.identity();
	//	MatrixTransform bultran = MatrixTransform(iden);
	//	bultran.addChild(bullet);
	//	objTrans.addChild(&parTrans);

	//	addBullet = false;
	//}
	objTrans.addChild(forestGroup);

	Matrix4 skyMatrix;
	skyMatrix.makeTranslate(0, 1, 0);
	MatrixTransform skyTrans = MatrixTransform(skyMatrix);
	Skybox sky = Skybox();
	skyTrans.addChild(&sky);
	objTrans.addChild(&skyTrans);

	Matrix4 identity = Matrix4();
	identity.identity();

	
	Floor floor = Floor();
	objTrans.addChild(&floor);

//	cout << enemies.size();
	for (std::vector<EnemyBox>::iterator it = enemies->begin(); it != enemies->end(); ++it) {
	//	objTrans.addChild(&(*it));
	}

	//objTrans.addChild(&enemies[0]);
	Matrix4 moveMatrix = Matrix4();
	moveMatrix.makeTranslate(-1, 0, -1);

	//Matrix4 bigMatrix = Matrix4();
	//bigMatrix.makeScale(2, 2, 2);
	//MatrixTransform moveTransform = MatrixTransform(bigMatrix);
	//
	//enemyBox.pos = enemyBox.newPosition();
	//moveTransform.addChild(&enemyBox);
	//objTrans.addChild(&moveTransform);
	//moveTransform.draw(identity);


	//Point light source
	Matrix4 pointLightMatrix = Matrix4();
	pointLightMatrix.makeTranslate(lightX, lightY, lightZ);
	displayLights(lightX, lightY, lightZ);
	MatrixTransform pointLightTrans = MatrixTransform(pointLightMatrix);
	Sphere pointLightSphere = Sphere();
	pointLightTrans.addChild(&pointLightSphere);
	//if (enablePointLight)
		//world.addChild(&pointLightTrans);

	//world.update(identity);
	world.draw(identity);
	world.update(identity);
	//world.drawBoundingSpheres(identity);

	//moveTransform.drawBoundingSpheres(identity);

	glPopMatrix();

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
	zoom.makeScale(10, 10, 10);
	//Matrix4 rotate;
	//rotate.identity();
	//rotate.makeRotateX(-30);
	Matrix4 translate;
	//translate.identity();
	translate.makeTranslate(0, -1.2, 0);


	finalMatrix.identity();
	finalMatrix = finalMatrix  * translate *zoom;
}

void Window::applyGlobalMatrix() {
	glLoadMatrixd(finalMatrix.getPointer());
}

Vector3 lastPoint;
int Movement;

void Window::processMouseFunction(int button, int state, int x, int y) {
	if (state == GLUT_UP) return;

	if (button == GLUT_LEFT_BUTTON || state == GLUT_DOWN){
		double angleX = camera->getAngleX();
		double angleY = camera->getAngleY();
		double x = -cos(angleX)*cos(angleY);
		double y = sin(angleY);
		double z = -cos(angleY)*sin(angleX);
		Vector3 pos = camera->getPosition();
		for (int i = 0; i < 3; i++) pos.m[i] = -pos.m[i];
		pos.m[1] += 0.125;
		Bullet *bullet = new Bullet(pos, Vector3(x,y,z),1);
		bullets->push_back(bullet);
	}

	/*Point point = Point{ x, y };
	switch (button) {
	case 0:
		Movement = ROTATE;
		lastPoint = trackBallMapping(point);

		break;
	case 2:
		Movement = ZOOM;
		lastPoint = Vector3(point.x, point.y, 0);
		break;
	}
	cout << "\n state" << state << " button" << button << " x" << x << " y" << y;*/
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
	
	//Point point = Point{ x, y };
	////Detect mouse movement:
	//Vector3 direction;
	//float pixel_diff, pixel_diffY;
	//float rot_angle, zoom_factor, zoom_factorY;
	//Vector3 curPoint;
	//switch (Movement)
	//{

	//case ROTATE: // Left-mouse button is being held down
	//{
	//	curPoint = trackBallMapping(point); // Map the mouse position to a logical
	//	// sphere location.
	//	direction = curPoint - lastPoint;
	//	float velocity = direction.length();
	//	cout << " v: " << velocity;
	//	if (velocity > 0.0001) // If little movement - do nothing.
	//	{
	//		//
	//		// Rotate about the axis that is perpendicular to the great circle connecting the mouse movements.
	//		//
	//		if (!lightMotionEnabled) {
	//			Vector3 rotAxis;
	//			rotAxis = rotAxis.cross(lastPoint, curPoint);
	//			rotAxis.normalize();
	//			rot_angle = velocity * m_ROTSCALE;
	//			//
	//			// We need to apply the rotation as the last transformation.
	//			// 1. Get the current matrix and save it.
	//			// 2. Set the matrix to the identity matrix (clear it).
	//			// 3. Apply the trackball rotation.
	//			// 4. Pre-multiply it by the saved matrix.
	//			//
	//			/*GLdouble modelMatrix[16];
	//			glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	//			Matrix4 objectXform = Matrix4(modelMatrix);
	//			glLoadIdentity();*/

	//			Matrix4 rotateMatrix = Matrix4();
	//			rotateMatrix.identity();
	//			rotateMatrix.makeRotate(-rot_angle, rotAxis);
	//			//glRotated(rot_angle, rotAxis.m[0], rotAxis.m[1], rotAxis.m[2]);

	//			finalMatrix = rotateMatrix * finalMatrix;
	//		}
	//		else {
	//			spotlightX = curPoint.m[0] * 10;
	//			spotlightY = curPoint.m[1] * 10;
	//			spotlightZ = 12 + curPoint.m[2] * 5;
	//			displaySpotlightCone();
	//		}

	//		//glMultMatrixd(objectXform.getPointer());
	//	}
	//	break;
	//}
	//case ZOOM: // Right-mouse button is being held down
	//	//
	//	// Zoom into or away from the scene based upon how far the 
	//	// mouse moved in the x-direction.
	//	// This implementation does this by scaling the eye-space.
	//	// This should be the first operation performed by the GL_PROJECTION matrix.
	//	// 1. Calculate the signed distance
	//	// a. movement to the left is negative (zoom out).
	//	// b. movement to the right is positive (zoom in).
	//	// 2. Calculate a scale factor for the scene s = 1 + a*dx
	//	// 3. Call glScalef to have the scale be the first transformation.
	//	//
	//	if (!lightMotionEnabled) {
	//		pixel_diff = point.x - lastPoint.m[0];
	//		zoom_factor = 1.0 + pixel_diff * m_ZOOMSCALE;
	//		scaleObject(zoom_factor);
	//	}
	//	else {
	//		pixel_diffY = point.y - lastPoint.m[1];
	//		zoom_factorY = 1.0 + pixel_diffY * m_ZOOMSCALE * 1.5;
	//		spotLightAngle *= zoom_factorY;
	//		displaySpotlightCone();
	//	}
	//	//
	//	// Set the current point, so the lastPoint will be saved properly below . 
	//	// 
	//	lastPoint.m[0] = point.x;
	//	lastPoint.m[1] = point.y;
	//	lastPoint.m[2] = 0;

	//	break;
	//}

	//displayCallback();
}

void Window::passiveMouseFunction(int x, int y){
	if (!enableMouse) {
		camera->updatePrev(x, y);
		return;
	}

	camera->updateMouse(x, y);

	Matrix4 rotX = camera->getRotX();
	Matrix4 rotY = camera->getRotY();

	finalMatrix = finalMatrix * rotX * rotY;
}



bool Window::collisionDetected(TargetBox *target, Bullet *bullet){
	Vector3 p1 = target->pos;
	Vector3 p2 = bullet->pos;
	Vector3 dia = p1 - p2;
	double dis = dia.dot(dia, bullet->dir);
	if (dis > bullet->speed) return false;
	Vector3 mid;
	for (int i = 0; i < 3; i++){
		mid.m[i] = p2.m[i] + dis*bullet->dir.m[i];
	}
	Vector3 fi = p1 - mid;
	double result = fi.length();
	return result <= (target->scale +bullet->radius);
}

bool Window::collisionDetected2(TargetBox *target, Bullet *bullet){
	Vector3 p1 = target->pos;
	Vector3 p2 = bullet->pos;
	Vector3 p3 = p1 - p2;
	double dis = p3.length();
	return dis <= (target->scale + (bullet->radius + Bullet::speed) / 2.0);
}
