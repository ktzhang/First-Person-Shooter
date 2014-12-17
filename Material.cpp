#include "Material.h"

#include <GL/glut.h>

using namespace std;

void Material::setSpecular(float* spec) {
	glMaterialfv(type, GL_SPECULAR, spec);
}

void Material::setShininess(float* shin) {
	glMaterialfv(type, GL_SHININESS, shin);
}

void Material::setEmission(float* emis) {
	glMaterialfv(type, GL_EMISSION, emis);
}

void Material::setColorIndexes(float* color) {
	glMaterialfv(type, GL_COLOR_INDEXES, color);
}

void Material::setAmbient(float* ambient) {
	glMaterialfv(type, GL_AMBIENT, ambient);
}

void Material::setDiffuse(float* diffuse) {
	glMaterialfv(type, GL_DIFFUSE, diffuse);
}

void Material::setAmbientAndDiffuse(float* both) {
	glMaterialfv(type, GL_AMBIENT_AND_DIFFUSE, both);
}