#include "Water.h"
#include <GL/glut.h>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <math.h>
#include "Group.h"
#include "Geode.h"
#include "Sphere.h"
#include "cube.h"
#include "MatrixTransform.h"
#include "Robot.h"
#include "Camera.h"

#include "Vector3.h"


using namespace std;
extern GLuint p;
extern GLuint* top;
extern GLuint* front;
extern GLuint* leftCube;
extern GLuint* rightCube;
extern GLuint* back;
extern Matrix4 finalMatrix;
extern int enableShaders;


void Water::initialize(double increment, int on) {
	double addValue = M_PI/2 * increment;
	double piValue = M_PI / 2;
	double factor = 0.1;
	double offset = -1;
	if (!on) {
		offset = -1;
		factor = 0;
	}

	anchors[0][0] = Vector3(-1, sin(piValue * 0 + addValue) * factor + offset, -1); // Set The Bezier Vertices
	anchors[0][1] = Vector3(-1, sin(piValue * 1 + addValue) * factor + offset, -.33);
	anchors[0][2] = Vector3(-1, sin(piValue * 2 + addValue) * factor + offset, 0.33);
	anchors[0][3] = Vector3(-1, sin(piValue * 3 + addValue) * factor + offset, 1);
	anchors[1][0] = Vector3(-.33, sin(piValue * 0 + addValue) * factor + offset, -1);
	anchors[1][1] = Vector3(-.33, sin(piValue * 1 + addValue) * factor + offset, -.33);
	anchors[1][2] = Vector3(-.33, sin(piValue * 2 + addValue) * factor + offset, .33);
	anchors[1][3] = Vector3(-.33, sin(piValue * 3 + addValue) * factor + offset, 1);
	anchors[2][0] = Vector3(.33, sin(piValue * 0 + addValue) * factor + offset, -1);
	anchors[2][1] = Vector3(.33, sin(piValue * 1 + addValue) * factor + offset, -.33);
	anchors[2][2] = Vector3(.33, sin(piValue * 2 + addValue) * factor + offset, .33);
	anchors[2][3] = Vector3(.33, sin(piValue * 3 + addValue) * factor + offset, 1);
	anchors[3][0] = Vector3(1, sin(piValue * 0 + addValue) * factor + offset, -1); // Set The Bezier Vertices
	anchors[3][1] = Vector3(1, sin(piValue * 1 + addValue) * factor + offset, -.33);
	anchors[3][2] = Vector3(1, sin(piValue * 2 + addValue) * factor + offset, 0.33);
	anchors[3][3] = Vector3(1, sin(piValue * 3 + addValue) * factor + offset, 1);
}

Vector3 Bernstein(float u, Vector3 *p) {
	Vector3    a, b, c, d, r;
	a = p[0];
	b = p[1];
	c = p[2];
	d = p[3];

	a.scale(pow(u, 3));
	b.scale(3 * pow(u, 2)*(1 - u));
	c.scale(3 * u*pow((1 - u), 2));
	d.scale(pow((1 - u), 3));

	r = a + b + c + d;

	return r;
}


long Factorial(long val){
	long Result = 1;
	for (long i = 2; i < val; ++i)
	{
		Result *= i;
	}
	return Result;
}

double Combination(long N, long R){
	return (Factorial(N) / ((Factorial(N - R) * Factorial(R))));
}


Vector3 calcTangent(float u, Vector3* points) {
	double c0 = Combination(2, 0) * pow(u, 0) * pow(1 - u, 2 - 0) * 3;
	double c1 = Combination(2, 1) * pow(u, 1) * pow(1 - u, 2 - 1) * 3;
	double c2 = Combination(2, 2) * pow(u, 2) * pow(1 - u, 2 - 2) * 3;
	Vector3 a = points[1] - points[0];
	a.scale(c0);
	Vector3 b = points[2] - points[1];
	b.scale(c1);
	Vector3 c = points[3] - points[2];
	c.scale(c1);
	Vector3 tangent = a + b + c;
	tangent.normalize();
	return tangent;
}


void Water::render() {

	glActiveTexture(GL_TEXTURE0);

	Camera cam = Camera();
	cam.dVector = Vector3(0, 0, 1);
	cam.eVector = Vector3(0, 0, 0);
	cam.upVector = Vector3(0, 1, 0);


	GLuint modelVMatIdx = glGetUniformLocation(p, "modelVMat");
	GLuint projMatIdx = glGetUniformLocation(p, "projMat");
	GLuint viewMat = glGetUniformLocation(p, "viewMat");

	GLuint topShader = glGetUniformLocation(p, "top");
	glUniform1i(topShader, 1);
	GLuint leftShader = glGetUniformLocation(p, "leftCube");
	glUniform1i(leftShader, 2);
	GLuint rightShader = glGetUniformLocation(p, "rightCube");
	glUniform1i(rightShader, 3);
	GLuint frontShader = glGetUniformLocation(p, "front");
	glUniform1i(frontShader, 4);
	GLuint backShader = glGetUniformLocation(p, "back");
	glUniform1i(backShader, 5);


	glBindTexture(GL_TEXTURE_2D, *top);



	if (enableShaders)
		glUseProgram(p);

	//Pass projection matrix to shader
	GLfloat projectionMatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
	//Pass to shader
	glUniformMatrix4fv(projMatIdx, 1, false, &projectionMatrix[0]);

	//Pass current modelview matrix to shader
	GLfloat modelViewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);
	
	glUniformMatrix4fv(modelVMatIdx, 1, false, &modelViewMatrix[0]);

	//GLfloat modelMatrix[16];
	//for (int q = 0; q < 4; q++)
	//{
	//	for (int t = 0; t < 4; t++)
	//	{
	//		modelMatrix[q * 4 + t] = finalMatrix.m[q][t];
	//	}
	//}

//	glUniformMatrix4fv(modelVMatIdx, 1, false, &modelMatrix[0]);
	if (enableShaders)
		glUseProgramObjectARB(p);

	glPointSize(19.0);
	glDisable(GL_BLEND);

	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	// specify texture coordinates for each vertex
	// note that textures are stored "upside down"
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//glVertex3f(anchors[i][j].m[0], anchors[i][j].m[1], anchors[i][j].m[2]);
		}
	}
	glEnd();


	glPointSize(6.0);
	glColor3f(1, 1, 1);

	glBegin(GL_POINTS);
	float perX = 0.0;
	float perY = 0.0;
	const int numSquares = 100;
	Vector3 inputX[4];
	Vector3 inputY[4];
	Vector3 tempX[4];
	Vector3 tempY[4];
	Vector3 tempXTangent[4];
	Vector3 tempYTangent[4];

	Vector3 point;
	Vector3 finalPoints[numSquares + 1][numSquares + 1];
	Vector3 finalNormals[numSquares + 1][numSquares + 1];

	for (int i = 0; i <= numSquares; i++) {
		for (int j = 0; j <= numSquares; j++) {
			perX = ((float)1 / (float)numSquares) * (float)i;
			perY = ((float)1 / (float)numSquares) * (float)j;
			
			
			for (int k = 0; k < 4; k++) {
				inputX[0] = anchors[0][k];
				inputX[1] = anchors[1][k];
				inputX[2] = anchors[2][k];
				inputX[3] = anchors[3][k];
				inputY[0] = anchors[k][0];
				inputY[1] = anchors[k][1];
				inputY[2] = anchors[k][2];
				inputY[3] = anchors[k][3];
				tempX[k] = Bernstein(perX, inputX);
				tempY[k] = Bernstein(perY, inputY);
			}
			point = Bernstein(perY, tempX);
			Vector3 tan = calcTangent(perY, tempX);
			Vector3 tan2 = calcTangent(perX, tempY);
			Vector3 finalTan = finalTan.cross(tan, tan2);

			finalNormals[i][j] = finalTan;
			finalPoints[i][j] = point;
			//glVertex3f(point.m[0], point.m[1], point.m[2]);

		}
	}
	glEnd();

/*
	int monkey_V_location = glGetUniformLocation(p, "V");
	cout << printf("monkey V location = %i\n", monkey_V_location);*/
	//glUseProgram (p);
	//glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, *top);
	glColor3f(1, 1, 1);

	for (int i = 1; i < numSquares; i++) {
		for (int j = 1; j < numSquares; j++) {
			glBegin(GL_QUADS);

			glNormal3f(finalNormals[i][j].m[0], finalNormals[i][j].m[1], finalNormals[i][j].m[2]);
			


			glVertex3f(finalPoints[i][j].m[0], finalPoints[i][j].m[1], finalPoints[i][j].m[2]);
			glVertex3f(finalPoints[i - 1][j].m[0], finalPoints[i - 1][j].m[1], finalPoints[i - 1][j].m[2]);
			glVertex3f(finalPoints[i - 1][j - 1].m[0], finalPoints[i - 1][j - 1].m[1], finalPoints[i - 1][j - 1].m[2]);
			glVertex3f(finalPoints[i][j - 1].m[0], finalPoints[i][j - 1].m[1], finalPoints[i][j - 1].m[2]);
			glEnd();
		}
	}


	glEnable(GL_BLEND);


	glUseProgramObjectARB(0);

}