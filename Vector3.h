#include <string>

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#define M_PI 3.14159265358979323846

class Vector3
{
protected:
public:
	Vector3& operator=(const Vector3&);
	double* getPointer();
	void identity();
	void transpose();
	void makeRotateY(double);

	double x;
	double y;
	double z;

	Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z){};	// constructor with three parameters for the vector coordinates
	Vector3 operator+(const Vector3& vector);			// overload operator '+' for addition
	Vector3 operator-(const Vector3& vector); //overload operator '-' for subtraction

	void negate(); //: negation
	void scale(double s); //: scale(multiplication with scalar value)
	double dot(const Vector3& vector1, const Vector3& vector2); //: dot product, returns result
	Vector3 cross(const Vector3& vector1, const Vector3& vector2); //: cross product, returns result and puts it in calling vector
	double length();// : length of the vector
	void normalize();// : normalize the vector(make it so that its length is equal to one)
	void print(std::string& comment);// : print x, y and z components of the vector after a comment string
};

#endif