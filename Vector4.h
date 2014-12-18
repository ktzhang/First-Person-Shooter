#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <string>
#include "Vector3.h"


#define M_PI 3.14159265358979323846

class Vector4
{
public:
	static const int numElements = 4;
	double m[numElements];

	Vector4::Vector4() {
		m[0] = 0;
		m[1] = 0;
		m[2] = 0;
		m[3] = 0;
	}

	Vector4::Vector4(double x, double y, double z, double w) {
		m[0] = x;
		m[1] = y;
		m[2] = z;
		m[3] = w;
	};	// constructor with three parameters for the vector coordinates
	Vector4 operator+(const Vector4& vector);			// overload operator '+' for addition
	Vector4 operator-(const Vector4& vector); //overload operator '-' for subtraction

	void dehomogenize(); //dehomogenize the vector (scale it so that its fourth component is equal to one)
	void print(std::string& comment);// : print m[0], y and z components of the vector after a comment string
	std::string toString();

	void normalize();
};

#endif