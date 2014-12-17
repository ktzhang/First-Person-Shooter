#include "GLee.h"
#include "Skybox.h"
#include <GL/glut.h>
extern GLuint* textures;
extern unsigned char* loadPPM(const char* filename, int& width, int& height);
extern GLuint* top;
extern GLuint* front;
extern GLuint* leftCube;
extern GLuint* rightCube;
extern GLuint* back;

extern GLuint* tex_cube;
extern GLuint p;

const double Skybox::SIDELEN = 2;

using namespace std;
void Skybox::render() {
	double halfLen = SIDELEN / 2;
	glActiveTexture(GL_TEXTURE0);
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	//glUseProgramObjectARB(p);

	glColor3f(1, 1, 1);


	// set the current drawing color to white to use original texture colors
	glBindTexture(GL_TEXTURE_2D, *front);

	glBegin(GL_QUADS);

	// set the current drawing color to white to use original texture colors

	// specify texture coordinates for each vertex
	// note that textures are stored "upside down"
	glTexCoord2f(0, 1); glVertex3f(-halfLen, -halfLen, -halfLen);
	glTexCoord2f(1, 1); glVertex3f(halfLen, -halfLen, -halfLen);
	glTexCoord2f(1, 0); glVertex3f(halfLen, halfLen, -halfLen);
	glTexCoord2f(0, 0); glVertex3f(-halfLen, halfLen, -halfLen);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *back);
	glBegin(GL_QUADS);
	// specify texture coordinates for each vertex
	// note that textures are stored "upside down"
	glTexCoord2f(0, 1); glVertex3f(halfLen, -halfLen, halfLen);
	glTexCoord2f(1, 1); glVertex3f(-halfLen, -halfLen, halfLen);
	glTexCoord2f(1, 0); glVertex3f(-halfLen, halfLen, halfLen);
	glTexCoord2f(0, 0); glVertex3f(halfLen, halfLen, halfLen);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *rightCube);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(halfLen, -halfLen, -halfLen);
	glTexCoord2f(1, 1); glVertex3f(halfLen, -halfLen, halfLen);
	glTexCoord2f(1, 0); glVertex3f(halfLen, halfLen, halfLen);
	glTexCoord2f(0, 0); glVertex3f(halfLen, halfLen, -halfLen);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *leftCube);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-halfLen, -halfLen, halfLen);
	glTexCoord2f(1, 1); glVertex3f(-halfLen, -halfLen, -halfLen);
	glTexCoord2f(1, 0); glVertex3f(-halfLen, halfLen, -halfLen);
	glTexCoord2f(0, 0); glVertex3f(-halfLen, halfLen, halfLen);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *top);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-halfLen, halfLen, -halfLen);
	glTexCoord2f(1, 1); glVertex3f(halfLen, halfLen, -halfLen);
	glTexCoord2f(1, 0); glVertex3f(halfLen, halfLen, halfLen);
	glTexCoord2f(0, 0); glVertex3f(-halfLen, halfLen, halfLen);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_LIGHTING);
}