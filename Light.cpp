#include "Light.h"

#include <iostream>
#include <GL/glut.h>

using namespace std;

Light::Light(GLenum sourceLight) {
	this->sourceLight = sourceLight;
}


void Light::setAmbient(float* ambient) {
	for (int i = 0; i < 4; i++) {
		this->ambient[i] = ambient[i];
	}
	glLightfv(sourceLight, GL_AMBIENT, diffuse);
}

void Light::setDiffuse(float* diffuse) {
	for (int i = 0; i < 4; i++) {
		this->diffuse[i] = diffuse[i];
	}
	glLightfv(sourceLight, GL_DIFFUSE, diffuse);
}

void Light::setSpotDirection(Vector3 direction) {
	float directionArray[3] = { direction.m[0], direction.m[1], direction.m[2] };
	glLightfv(sourceLight, GL_SPOT_DIRECTION, directionArray);
}

void Light::setExponent(float exponent) {
	glLightf(sourceLight, GL_SPOT_EXPONENT, exponent);
}

void Light::setSpecular(float* specular) {
	for (int i = 0; i < 4; i++) {
		this->specular[i] = specular[i];
	}	
	glLightfv(sourceLight, GL_SPECULAR, specular);
}

void Light::setCutoff(float cutoff) {
	glLightf(sourceLight, GL_SPOT_CUTOFF, cutoff);
}

void Light::setPosition(float* position) {
	glLightfv(sourceLight, GL_POSITION, position);
}

void Light::setConstantAttenuation(float value) {
	glLightf(sourceLight, GL_CONSTANT_ATTENUATION, value);
}

void Light::setLinearAttenuation(float value) {
	glLightf(sourceLight, GL_LINEAR_ATTENUATION, value);
}

void Light::setQuadraticAttenuation(float value) {
	glLightf(sourceLight, GL_QUADRATIC_ATTENUATION, value);
}

void Light::enable() {
	glEnable(sourceLight);
	glLightfv(sourceLight, GL_AMBIENT, ambient);
	glLightfv(sourceLight, GL_DIFFUSE, diffuse);
	glLightfv(sourceLight, GL_SPECULAR, specular);
}

void Light::disable() {
	const float noLight[4] = { 0, 0, 0, 0 };
	glDisable(sourceLight);
	glLightfv(sourceLight, GL_DIFFUSE, noLight);
	glLightfv(sourceLight, GL_SPECULAR, noLight);
}