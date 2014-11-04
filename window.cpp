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

using namespace std;

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
extern vector<float> imageNums[2];

int viewMode = 4; // 0 = ball, 1/2 = house, 3 = bunny, 4 = dragon
int cameraDistance = 20;
int fov = 60;
int prevViewMode = -1;
double imageScale = 1;
int rotate = 0;
int imageSpinAngle = 0;
int rotateFactor = 0;

//----------------------------------------------------------------------------
// Callback method of keyboard input
void Window::processNormalKeys(unsigned char key, int x, int y) 
{
	double transFactor = 0.5;
	double orbitDeg = 10;
	double scaleFactorTransform = 0.1;
	switch (key) {
		//'t' for spinning clockwise or counter clockwise
	case 116:
		if (viewMode == 3 || viewMode == 4) {
			if (rotateFactor == 1) {
				rotateFactor = 0;
			}
			else {
				rotateFactor = 1;
			}

		}
		else if (viewMode == 0) {
			Globals::cube.changeSpinDirection();
		}
		break;

		//'x' left 
	case 120:
		Globals::cube.translateCube(-transFactor, 0, 0);
		break;

		// 'X' right
	case 88:
		Globals::cube.translateCube(transFactor, 0, 0);
		break;

		// 'y' down 
	case 121:
		Globals::cube.translateCube(0, -transFactor, 0);
		break;

		// 'Y' up
	case 89:
		Globals::cube.translateCube(0, transFactor, 0);
		break;

		// 'z' in
	case 122:
		Globals::cube.translateCube(0, 0, transFactor);
		break;

		// 'Z' out
	case 90:
		Globals::cube.translateCube(0, 0, -transFactor);
		break;

		// 'r' reset
	case 114:
		Globals::cube.reset();
		break;

		// 'o' orbit counterclockwise
	case 111:
		Globals::cube.orbitCube(-orbitDeg);
		break;

		// 'O' orbit clockwise
	case 79:
		Globals::cube.orbitCube(orbitDeg);
		break;


		// 's' scale down
	case 115:
		if (viewMode == 3 || viewMode == 4) {
			imageScale -= scaleFactorTransform;
		}
		else if (viewMode == 0) {
			Globals::cube.scaleCube(-scaleFactorTransform);
		}
		break;

		// 'S' scale up
	case 83:
		if (viewMode == 3 || viewMode == 4) {
			imageScale += scaleFactorTransform;
		}
		else if (viewMode == 0) {
			Globals::cube.scaleCube(scaleFactorTransform);
		}
		break;
	}
}


void Window::processFunctionKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		viewMode = 0;
	}
	else if (key == GLUT_KEY_F2) {
		viewMode = 1;
	}
	else if (key == GLUT_KEY_F3) {
		viewMode = 2;
	} 
	else if (key == GLUT_KEY_F4) {
		viewMode = 4;
	}
	else if (key == GLUT_KEY_F5) {
		viewMode = 3;
	}
}

	

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
	if (viewMode == 0) {
		Globals::cube.animate();   // rotate cube; if it spins too fast try smaller values and vice versa
	}
	displayCallback();         // call display routine to show the cube
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
	//glLoadIdentity();
	gluPerspective(fov, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
}


struct CameraVectors {
	Vector3 centerVector;
	Vector3 dVector;
	Vector3 upVector;
};

int nVerts = 42;    // your vertex array needs to have this many entries

// These are the x,y,z coordinates of the vertices of the triangles
float vertices[] = {
	-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
	-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
	4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
	4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
	4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
	-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

	-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
	-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
	4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
	-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
	4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

// These are the RGB colors corresponding to the vertices, in the same order
float colors[] = {
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
	0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

	0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
	0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
	1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
	0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
	0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

// The index data stores the connectivity of the triangles; 
// index 0 refers to the first triangle defined above
int indices[] = {
	0, 2, 3, 0, 1, 2,      // front face
	4, 6, 7, 4, 5, 6,      // left face
	8, 10, 11, 8, 9, 10,     // back face
	12, 14, 15, 12, 13, 14,   // right face
	16, 18, 19, 16, 17, 18,   // top face
	20, 22, 23, 20, 21, 22,   // bottom face

	24, 26, 27, 24, 25, 26,   // grass
	28, 29, 30,             // front attic wall
	31, 33, 34, 31, 32, 33,   // left slope
	35, 37, 38, 35, 36, 37,   // right slope
	39, 40, 41 };            // rear attic wall

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	int shouldPrint = true;
	if (viewMode == prevViewMode) {
		shouldPrint = false;
	}
	prevViewMode = viewMode;

	// house
	if (viewMode == 1 || viewMode == 2) {
		glDisable(GL_LIGHTING);
		// Tell OpenGL what ModelView matrix to use:
		CameraVectors cameraVectors[2];
		cameraVectors[0] = { Vector3(0, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0) };
		cameraVectors[1] = { Vector3(-15, 5, 10), Vector3(-5, 0, 0), Vector3(0, 1, 0.5) };

		Camera camera[2];
		for (int i = 0; i < 2; i++) {
			camera[i].eVector = cameraVectors[i].centerVector;
			camera[i].dVector = cameraVectors[i].dVector;
			camera[i].upVector = cameraVectors[i].upVector;
		}

		Matrix4 cameraMatrix = *(camera[viewMode - 1].getInvert());
		glLoadMatrixd(cameraMatrix.getPointer());
		std::string hiThere = "\n";
		cameraMatrix.print(hiThere);
		OutputDebugString(hiThere.c_str());

		glBegin(GL_TRIANGLES);
		int vertexNum[3];
		int vertexIndex;
		int colorIndex;

		for (int i = 0; i < 60; i += 3) {
			vertexNum[0] = indices[i];
			vertexNum[1] = indices[i + 1];
			vertexNum[2] = indices[i + 2];
			printf("%d %d %d \n", vertexNum[0], vertexNum[1], vertexNum[2]);
			//Getting the color of one index
			colorIndex = 3 * vertexNum[0];
			glColor3f(colors[colorIndex], colors[colorIndex + 1], colors[colorIndex +2]);
			
			for (int j = 0; j < 3; j++) {
				vertexIndex = vertexNum[j] * 3;
				glVertex3f(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]);
				printf("vertex (%d - %f, %f, %f) \n", vertexIndex,
					vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]);
			}
		}
		glEnd();
	}

	// cube
	else if(viewMode == 0) {
		Matrix4 glmatrix;
		glmatrix = Globals::cube.getMatrix();
		glLoadMatrixd(glmatrix.getPointer());
		
		// Draw all six faces of the cube:
		glBegin(GL_QUADS);
		glEnable(GL_LIGHTING);

		glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
		// To change the color of the other faces you will need to repeat this call before each face is drawn.
		// Draw front face:
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(5.0, -5.0, 5.0);
		glVertex3f(-5.0, -5.0, 5.0);

		// Draw left side:
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glVertex3f(-5.0, -5.0, 5.0);

		// Draw right side:
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(5.0, -5.0, -5.0);
		glVertex3f(5.0, -5.0, 5.0);

		// Draw back face:
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-5.0, 5.0, -5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(5.0, -5.0, -5.0);
		glVertex3f(-5.0, -5.0, -5.0);

		// Draw top side:
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, 5.0);
		glVertex3f(5.0, 5.0, -5.0);
		glVertex3f(-5.0, 5.0, -5.0);

		// Draw bottom side:
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(-5.0, -5.0, -5.0);
		glVertex3f(5.0, -5.0, -5.0);
		glVertex3f(5.0, -5.0, 5.0);
		glVertex3f(-5.0, -5.0, 5.0);
		glEnd();
	}

	// images
	else if (viewMode == 3 || viewMode == 4) {
		//Load dragon
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glBegin(GL_POINTS);

		int imageNumber = viewMode - 3;

		float maxX = -10000;
		float maxY = -10000;
		float maxZ = -10000;

		float minX = 10000;
		float minY = 10000;
		float minZ = 10000;

		for (std::vector<float>::size_type i = 0; i < imageNums[imageNumber].size(); i+=6) {
			if (imageNums[imageNumber][i] > maxX) {
				maxX = imageNums[imageNumber][i];
			}
			if (imageNums[imageNumber][i + 1] > maxY) {
				maxY = imageNums[imageNumber][i + 1];
			}
			if (imageNums[imageNumber][i + 2] > maxZ) {
				maxZ = imageNums[imageNumber][i + 3];
			}
			if (imageNums[imageNumber][i] < minX) {
				minX = imageNums[imageNumber][i];
			}
			if (imageNums[imageNumber][i + 1] < minY) {
				minY = imageNums[imageNumber][i + 1];
			}
			if (imageNums[imageNumber][i + 2] < minZ) {
				minZ = imageNums[imageNumber][i + 2];
			}
			glColor3f(imageNums[imageNumber][i + 3], imageNums[imageNumber][i + 4], imageNums[imageNumber][i + 5]);
			glNormal3d(imageNums[imageNumber][i+3], imageNums[imageNumber][i+4], imageNums[imageNumber][i+5]);
			glVertex3d(imageNums[imageNumber][i], imageNums[imageNumber][i+1], imageNums[imageNumber][i+2]);
			
		}
		glEnd();

		//Finding translation to the center
		float meanX = (maxX + minX) / 2;
		float meanY = (maxY + minY) / 2;
		float meanZ = (maxZ + minZ) / 2;

		if (shouldPrint)
			printf("(Min X = %f, Min Y = %f, Min Z = %f, \n Max X = %f, Max Y = %f, Max Z = %f) \n", minX, minY, minZ, maxX, maxY, maxZ);

		string comment = "";
		Matrix4 translate;
		translate.makeTranslate(-meanX, -meanY, -meanZ);
		translate.print(comment);

		if (shouldPrint)
			cout << "Translate Matrix:: " << comment << "\n \n";

		double windowSize = (cameraDistance * tan(((fov / 2) / 180.0) * M_PI)) * 2;
		double scaleFactor = windowSize / ((maxX - minX));

		comment = "";
		Matrix4 scale;
		scale.makeScale(imageScale * scaleFactor, imageScale * scaleFactor, imageScale* scaleFactor);
		scale.print(comment);

		if (shouldPrint)
			cout << "Scale Matrix:: " << comment << "\n \n";

		Matrix4 rotate;
		if (rotateFactor) {
			imageSpinAngle += 1;
		}
		rotate.makeRotateY(imageSpinAngle * rotateFactor);

		Matrix4 finalMatrix;
		finalMatrix.identity();
		finalMatrix = scale * translate * rotate;

		comment = "";
		finalMatrix.print(comment);


		//if (viewMode ==3 )
		glLoadMatrixd(finalMatrix.getPointer());
		//if (shouldPrint)
			cout << "Final Matrix:: " << comment << "\n \n";
	}

	glFlush();
	glutSwapBuffers();
}