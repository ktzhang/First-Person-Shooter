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


using namespace std;
void Skybox::render() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);

	// set the current drawing color to white to use original texture colors
	glBindTexture(GL_TEXTURE_2D, *front);

	glBegin(GL_QUADS);

	// set the current drawing color to white to use original texture colors

	// specify texture coordinates for each vertex
	// note that textures are stored "upside down"
	glTexCoord2f(0, 1); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, -1);
	glTexCoord2f(0, 0); glVertex3f(-1, 1, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *back);
	glBegin(GL_QUADS);
	// specify texture coordinates for each vertex
	// note that textures are stored "upside down"
	glTexCoord2f(0, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 1); glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *rightCube);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(1, -1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(1, 1, -1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *leftCube);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
	glTexCoord2f(1, 1); glVertex3f(-1, -1, -1);
	glTexCoord2f(1, 0); glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, *top);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
	glTexCoord2f(1, 1); glVertex3f(1, 1, -1);
	glTexCoord2f(1, 0); glVertex3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(-1, 1, 1);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}