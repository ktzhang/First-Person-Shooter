#ifndef _LIGHTS_H_
#define _LIGHTS_H_

#include <string>
#include <GL/glut.h>

#include "Vector4.h"
#include "Matrix4.h"
#include "Vector3.h"

using namespace std;

class Light
{
public:
	GLenum sourceLight; // GL_LIGHT#

	float ambient[4];
	float diffuse[4];
	float specular[4];

	Light::Light() {
		sourceLight = GL_LIGHT0;
	}
	Light(GLenum sourceLight);
	void setAmbient(float* ambient);
	void setDiffuse(float* diffuse);
	void setSpecular(float* specular);
	void setMatrixPosition(float* position);
	void setSpotDirection(Vector3 direction);
	void setMatrixDirection(float* direction);
	void setExponent(float exponent);
	void setCutoff(float cutoff);
	void setPosition(float* position);
	void setConstantAttenuation(float value);
	void setLinearAttenuation(float value);
	void setQuadraticAttenuation(float value);
	void enable();
	void disable();
};

#endif
