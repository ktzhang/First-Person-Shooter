#ifdef _WIN32
#include <windows.h>
#include "Rasterizer.h"
#endif

#include "Camera.h"
#include "Vector4.h"
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include "Reader.h"
#include <fstream>
#include "ZBuffer.h"


using namespace std;

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];

// Class variables
static Camera cameraMatrix;
static Matrix4 projMatrix;
static Matrix4 viewportMatrix;
static Matrix4* modelMatrix;

double fovDeg = 0;
double fovRad = 0;
double scaleFactor;

Vector3 lightSource = Vector3(-10, 10, 10);
int lightIntensity = 400;

int shouldRotate = 0;
int rotateDeg = 0;
int scale = 100;
ZBuffer zBuffer;
double cameraDistance = 20;
Reader bunny;
Reader dragon;
Reader *currentObj = &bunny;


//States
int shadingEnabled = 0;
int zBufferEnabled = 0;
int pointSizeEnabled = 0;
int sphericalCoordEnabled = 0;

void loadData()
{
	bunny = Reader("bunny.xyz");
	dragon = Reader("dragon.xyz");
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}

void drawPointSize(int x, int y, float r, float g, float b, double zDepth) {
	int size = 0;
	if (pointSizeEnabled) {
		if (zDepth < 1) {
			size = 1;
		}
		if (zDepth < 0.666) {
			size = 2;
		}
		if (zDepth < 0.5) {
			size = 3;
		}
		if (zDepth < 0.4) {
			size = 4;
		}
		if (zDepth < 0.3) {
			size = 5;
		}
		if (zDepth < 0.2) {
			size = 7;
		}
		if (!sphericalCoordEnabled) {

			for (int newY = y - size; newY <= y + size; newY++) {
				for (int newX = x - size; newX < x + size; newX++) {
					drawPoint(newX, newY, r, g, b, zDepth);
				}
			}
		}
		else {
			for (int newY = y - size; newY <= y + size; newY++) {
				for (int newX = x - size; newX < x + size; newX++) {
					if (((newY - y) * (newY - y) + (newX - x) * (newX - x)) <= size * size) {
						drawPoint(newX, newY, r, g, b, zDepth);
					}
				}
			}

		}
	}
	else {
		drawPoint(x, y, r, g, b, zDepth);
	}

}
// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b, double zDepth)
{
	int offset = y*window_width * 3 + x * 3;
	int size;
	
	if (zBufferEnabled && !zBuffer.checkAndReplace(x, y, zDepth)) {
		return;
	}
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}


// Called to rasterize each vertex with a color
void rasterizeVertex(Vector4 input, Color color) 
{
	Matrix4* tempCamera = cameraMatrix.getInvert();
	
	Vector4* finalVector = new Vector4(0, 0, 0, 0);
	*finalVector = viewportMatrix * projMatrix  * *modelMatrix * input;
	//finalVector->dehomogenize();

	Matrix4 multMatrix = viewportMatrix * projMatrix * *(tempCamera) * *modelMatrix;
	//*finalVector = input * *(tempCamera)* cameraMove * projMatrix;
	//multMatrix.printToSt();
	
	int display = 0;
	if (display) {
		cout << "\nInput : " << input.toString() << "\n";
		cout << "matrix";
		multMatrix.printToSt();

		cout << "\n Model Matrix";
		//modelMatrix.printToSt();

		cout << "\n ViewPort Matrix";
		viewportMatrix.printToSt();

		cout << "\n Proj Matrix";
		projMatrix.printToSt();

		cout << "\n Temp cam Matrix";
		tempCamera->printToSt();

	}

	double zDepth = finalVector->m[2] / finalVector->m[3];

	// Rounding to the nearest int
	int xCoord = (finalVector->m[0] / finalVector->m[3])+0.5;
	int yCoord = (finalVector->m[1] / finalVector->m[3])+0.5;

	if (display) {
		cout << "\nx coord = " << xCoord << " - y coord = " << yCoord;
		cout << "\n--------------\n";
	}

	
	drawPointSize(xCoord, yCoord, color.r, color.g, color.b, zDepth);
	

}
void rasterize()
{
	//Test rasterization - rasterizing a house
	if (false) {
		int vertexNum[3];
		int vertexIndex;
		int colorIndex;
		for (int i = 0; i < 60; i += 3) {
			vertexNum[0] = indices[i];
			vertexNum[1] = indices[i + 1];
			vertexNum[2] = indices[i + 2];
			//printf("%d %d %d \n", vertexNum[0], vertexNum[1], vertexNum[2]);
			//Getting the color of one index
			colorIndex = 3 * vertexNum[0];
			Color color;
			color.r = colors[colorIndex];
			color.g = colors[colorIndex + 1];
			color.b = colors[colorIndex + 2];
			for (int j = 0; j < 3; j++) {
				vertexIndex = vertexNum[j] * 3;
				rasterizeVertex(Vector4(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2], 1), color);
				//printf("\n vertex (%d - %f, %f, %f) \n", vertexIndex,
				//	vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]);
			}
		}
	}

	vector<string>::iterator it; // declare an iterator to a vector of strings
	// now start at from the beginning
	// and keep iterating over the element till you find
	// nth element...or reach the end of vector.
	double objSize = currentObj->getSize();
	double meanX = currentObj->getMeanX();
	double meanY = currentObj->getMeanY();
	double meanZ = currentObj->getMeanZ();
	vector<Vector4> posVectors = currentObj->getPosVectors();
	vector<Vector4> normalVectors = currentObj->getNormalVectors();

	int i = 0;
	for (std::vector<Vector4>::size_type i = 0; i < posVectors.size(); i += 3) {
		//Set scale factor
		double windowSize = (cameraDistance * tan(fovRad/2) * 2);
		scaleFactor = windowSize / objSize;
		//scaleFactor = windowWidth / objSize;
		scaleFactor = scale;

		Matrix4 scaleMatrix;
		scaleMatrix.identity();
		scaleMatrix.makeScale(scaleFactor, scaleFactor, scaleFactor);

		Matrix4 moveMatrix;
		moveMatrix.makeTranslate(-meanX, -meanY, -meanZ);

		Matrix4 rotateMatrix;
		rotateMatrix.makeRotateY(rotateDeg);

		modelMatrix = new Matrix4();
		modelMatrix->identity();
		*modelMatrix = scaleMatrix * moveMatrix * rotateMatrix;

		//Coloring the model
		Vector4 po = posVectors[i];
		po = *(modelMatrix) * po;
		Vector3 currentPos = Vector3(po.m[0], po.m[1], po.m[2]);
		Vector3 newLightPos = lightSource - currentPos;
		double colorValueLi = 1 / (newLightPos.length() * newLightPos.length());

		newLightPos.normalize();
		Vector4 adjustedNormal = *(modelMatrix)* normalVectors[i];
		Vector3 newNormal = Vector3(adjustedNormal.m[0], adjustedNormal.m[1], adjustedNormal.m[2]);
		newNormal.normalize();
		double dotProduct = (newLightPos.dot(newNormal, newLightPos));
		double colorValue = (lightIntensity / M_PI) * colorValueLi * dotProduct;

		Color color;
		if (shadingEnabled) {
			color.r = colorValue;
			color.g = colorValue;
			color.b = colorValue;
		}
		else {
			color.r = 1;
			color.g = 1;
			color.b = 1;
		}
		rasterizeVertex(posVectors[i], color);
	}

	//Draw point for each triangle
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
}



void keyboardCallback(unsigned char key, int, int)
{
	cerr << "Key pressed: " << key << endl;

	switch (key) {
	case 'r':
		rotateDeg += 30;
		displayCallback();
		break;
	case 'R':
		rotateDeg -= 30;
		displayCallback();
		break;
	case 's':
		scale += 10;
		displayCallback();
		break;
	case 'S':
		scale -= 10;
		displayCallback();
		break;
	case '1':
		shadingEnabled = 0;
		displayCallback();
		break;
	case '2':
		shadingEnabled = 1;
		displayCallback();
		break;
	case '3':
		zBufferEnabled = !zBufferEnabled;
		displayCallback();
		break;
	case '4':
		pointSizeEnabled = !pointSizeEnabled;
		displayCallback();
		break;
	case '5':
		sphericalCoordEnabled = !sphericalCoordEnabled;
		displayCallback();
	}
}

void processFunctionKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		currentObj = &bunny;
		displayCallback();
	}
	else if (key == GLUT_KEY_F2) {
		currentObj = &dragon;
		displayCallback();
	}
}

void displayCallback()
{
	clearBuffer();
	if (zBufferEnabled)	zBuffer.resetBuffer();
	rasterize();
	cout << "Display";
	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

struct CameraVectors {
	Vector3 centerVector;
	Vector3 dVector;
	Vector3 upVector;
};

void setCameraMatrix()
{
	CameraVectors cameraVectors[2];
	cameraVectors[0] = { Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0) };
	cameraVectors[1] = { Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5) };
	
	Camera camera[2];
	for (int i = 0; i < 2; i++) {
		camera[i].eVector = cameraVectors[i].centerVector;
		camera[i].dVector = cameraVectors[i].dVector;
		camera[i].upVector = cameraVectors[i].upVector;
	}
	cameraMatrix = camera[0];
	
}

double degToRad(double deg)
{
	return deg * 180 / M_PI;
}

void setProjectionMatrix() 
{
	double left = -10.0;
	double right = 10.0;
	double bottom = -10.0;
	double top = 10.0;
	double nearV = 10.0;
	double farV = 1000.0;

	fovRad = 2 * atan((top - bottom) / nearV);
	fovDeg = degToRad(fovRad);

	double matrixInput[4][4] = {
		{ 2 * nearV / (right - left), 0, (right + left) / (right - left), 0 },
		{ 0, 2 * nearV / (top - bottom), (top + bottom) / (top - bottom), 0 },
		{ 0, 0, -1 * (farV + nearV) / (farV - nearV), -2 * farV*nearV / (farV - nearV) },
		{ 0, 0, -1, 0 }
	};

	projMatrix.identity();
	projMatrix = Matrix4(matrixInput);

	projMatrix.transpose();

	Matrix4 cameraMove;
	cameraMove.identity();
	cameraMove.makeTranslate(0, 0, -cameraDistance);

	projMatrix = projMatrix * cameraMove;
}

void setViewportMatrix() 
{
	double x = window_width;
	double y = window_height;
	double xStart = 0;
	double yStart = 0;

	double matrixInput[4][4] = {
		{ (x - xStart) / 2, 0, 0, (x + xStart) / 2}, 
		{ 0, (y - yStart) / 2, 0, (y + yStart) / 2},
		{ 0, 0, 0.5, 0.5 },
		{ 0, 0, 0, 1 }
	};

	viewportMatrix.identity();
	viewportMatrix = Matrix4(matrixInput);
	viewportMatrix.transpose();
}

void idleCallback()
{

}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;

	setProjectionMatrix();
	setViewportMatrix();
	setCameraMatrix();

	zBuffer = ZBuffer(window_width, window_height);

	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	displayCallback();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	setProjectionMatrix();
	setViewportMatrix();
	setCameraMatrix();

	zBuffer = ZBuffer(window_width, window_height);

	loadData();

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(processFunctionKeys);
	glutIdleFunc(idleCallback);

	glutMainLoop();
}

