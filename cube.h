#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"

class Cube
{
  protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double angle;                   // rotation angle [degrees]
	double orbitAngle;				// rotation angle orbit
	double origin[3];

  public:
    Cube();   // Constructor
	int spinDirection;

    Matrix4& getMatrix();
    Matrix4 spin(double);      // spin cube [degrees]
	void Cube::translateCube(double x, double y, double z);
	void Cube::animate();
	void Cube::changeSpinDirection();
	void Cube::orbitCube(double deg);
	void Cube::reset();
};

#endif

