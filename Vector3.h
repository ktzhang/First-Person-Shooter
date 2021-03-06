#include <string>

#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include "Vector4.h"

#define M_PI 3.14159265358979323846

class Vector3
{
protected:
public:
	static const int numElements = 3;
	double m[numElements];

	Vector3::Vector3(){
		m[0] = 0;
		m[1] = 1;
		m[2] = 2;
	}
	Vector3::Vector3(double x, double y, double z) {
		m[0] = x;
		m[1] = y;
		m[2] = z;
	};	// constructor with three parameters for the vector coordinates
	
	Vector3::Vector3(double input[]);

	Vector3 operator+(const Vector3& vector);			// overload operator '+' for addition
	Vector3 operator-(const Vector3& vector); //overload operator '-' for subtraction

	void negate(); //: negation
	void scale(double s); //: scale(multiplication with scalar value)
	double dot(const Vector3& vector1, const Vector3& vector2); //: dot product, returns result
	Vector3 cross(const Vector3& vector1, const Vector3& vector2); //: cross product, returns result and puts it in calling vector
	double length();// : length of the vector
	double angleBetween( Vector3& vector1,  Vector3& vector2);
	
	void normalize();// : normalize the vector(make it so that its length is equal to one)
	void print(std::string& comment);// : print x, y and z components of the vector after a comment string
	std::string toString();
};

#endif