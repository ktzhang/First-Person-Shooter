#include <GL\glut.h>
#include <GL\GL.h>
#include "GLee.h"
#include <string.h>


using namespace std;
class MapTex
{
public:
	MapTex();
	~MapTex();

	bool load();
	void loadTexture();
	void Bind(GLenum TextureUnit);

private:
	GLuint m_textureObj;
};