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


using namespace std;

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];

// Class variables
static Matrix4 modelMatrix;
static Camera cameraMatrix;
static Matrix4 projMatrix;
static Matrix4 viewportMatrix;


double cameraDistance = 20;
Reader bunny;
Reader dragon;

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

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*window_width * 3 + x * 3;
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}


// Called to rasterize each vertex with a color
void rasterizeVertex(Vector4 input, Color color) 
{
	Matrix4* tempCamera = cameraMatrix.getInvert();

	Matrix4* cameraMove = new Matrix4();
	cameraMove->identity();
	cameraMove->makeTranslate(0, 0, -20);

	//Order of multiplying matrix
	//Vector4 * finalVector = new Vector4();
	
	Vector4* finalVector = new Vector4(0, 0, 0, 0);
	*finalVector = projMatrix * *(cameraMove) * *(tempCamera) * input;
	finalVector->dehomogenize();

	Matrix4 multMatrix = projMatrix * *(cameraMove)* *(tempCamera);
	//*finalVector = input * *(tempCamera)* cameraMove * projMatrix;
	multMatrix.printToSt();

	/*cout << "matrix \n";
	multMatrix.printToSt();

	cout << input.toString();

	cout << "Proj Matrix \n";
	projMatrix.printToSt();

	cout << "Cam Matrix \n";
	cameraMove->printToSt();

	cout << "Temp cam Matrix \n";
	tempCamera->printToSt();

	cout << "Model \n";
	modelMatrix.printToSt();*/

	//Vector4 finalVector = input * modelMatrix * *(tempCamera) * cameraMove * projMatrix;
	//finalVector->dehomogenize();

	cout << "\n" << finalVector->toString();

	double xCoord = finalVector->m[0] / finalVector->m[3];
	double yCoord = finalVector->m[1] / finalVector->m[3];

	//Finally drawing points on the canvas
	drawPoint(xCoord, yCoord, color.r, color.g, color.b);
}
void rasterize()
{


	//Test matrix multiplication
	Matrix4 test;
	test.identity();
	test.makeTranslate(0, 0, 30);
	test.printToSt();

	Vector4 v(1, 2, 3, 4);
	v = test*v;

	cout << "\n" << v.toString();

	//Test rasterization - rasterizing a house
	//int vertexNum[3];
	//int vertexIndex;
	//int colorIndex;

	//for (int i = 0; i < 60; i += 3) {
	//	vertexNum[0] = indices[i];
	//	vertexNum[1] = indices[i + 1];
	//	vertexNum[2] = indices[i + 2];
	//	printf("%d %d %d \n", vertexNum[0], vertexNum[1], vertexNum[2]);
	//	//Getting the color of one index
	//	colorIndex = 3 * vertexNum[0];
	//	Color color;
	//	color.r = colors[colorIndex];
	//	color.g = colors[colorIndex + 1];
	//	color.b = colors[colorIndex + 2];



	//	for (int j = 0; j < 3; j++) {
	//		vertexIndex = vertexNum[j] * 3;
	//		rasterizeVertex(Vector4(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2], 1), color);
	//		printf("vertex (%d - %f, %f, %f) \n", vertexIndex,
	//			vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]);
	//	}
	//}



	vector<string>::iterator it; // declare an iterator to a vector of strings
	// now start at from the beginning
	// and keep iterating over the element till you find
	// nth element...or reach the end of vector.

	vector<Vector4> posVectors = bunny.getPosVectors();
	vector<Vector4> normalVectors = bunny.getNormalVectors();

	int i = 0;
	for (std::vector<Vector4>::size_type i = 0; i < posVectors.size(); i += 3) {
		Color color;
		color.r = normalVectors[i].m[0];
		color.g = normalVectors[i].m[1];
		color.b = normalVectors[i].m[2];
		rasterizeVertex(posVectors[i], color);
	}

	//Draw point for each triangle
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
}

// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;

	setProjectionMatrix();
	setViewportMatrix();

	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
	cerr << "Key pressed: " << key << endl;
}

void displayCallback()
{
	clearBuffer();
	rasterize();

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

void setModelMatrix() 
{
	modelMatrix.identity();
}

void setProjectionMatrix() 
{
	double left = -10.0;
	double right = 10.0;
	double bottom = -10.0;
	double top = 10.0;
	double nearV = 10.0;
	double farV = 1000.0;

	double matrixInput[4][4] = {
		{ 2 * nearV / (right - left), 0, (right + left) / (right - left), 0 },
		{ 0, 2 * nearV / (top - bottom), (top + bottom) / (top - bottom), 0 },
		{ 0, 0, -1 * (farV + nearV) / (farV - nearV), -2 * farV*nearV / (farV - nearV) },
		{ 0, 0, -1, 0 }
	};

	projMatrix.identity();
	projMatrix = Matrix4(matrixInput);
	projMatrix.transpose();
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	setProjectionMatrix();
	setViewportMatrix();
	setCameraMatrix();

	loadData();

	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutMainLoop();
}