#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <GL/glut.h>
using namespace std;

class Material
{
private:
	static const GLenum Material::type = GL_FRONT_AND_BACK;
public:
	static void setSpecular(float* spec);
	static void setShininess(float* shin);
	static void setEmission(float* emis);
	static void setColorIndexes(float* color);
	static void setAmbient(float* ambient);
	static void setDiffuse(float* diffuse);
	static void setAmbientAndDiffuse(float* both);
};

#endif