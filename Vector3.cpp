#include "Vector3.h"
#include "math.h"

#include <string>
#include <sstream>

Vector3::Vector3(double input[]) {
	for (int i = 0; i < Vector3::numElements; i++) {
		this->m[i] = input[i];
	}
}

Vector3 Vector3::operator+(const Vector3& vector) {
	Vector3 temp = Vector3();
	for (int i = 0; i < Vector3::numElements; i++) {
		temp.m[i] = vector.m[i] + this->m[i];
	}
	return temp;
}

Vector3 Vector3::operator-(const Vector3& vector) {
	double temp[Vector3::numElements];
	for (int i = 0; i < Vector3::numElements; i++) {
		temp[i] = this->m[i] - vector.m[i];
	}
	return Vector3(temp);
}

void Vector3::negate() {
	for (int i = 0; i < Vector3::numElements; i++) {
		this->m[i] = -this->m[i];
	}
}

void Vector3::scale(double s) {
	for (int i = 0; i < Vector3::numElements; i++) {
		this->m[i] = this->m[i]*s;
	}
}

double Vector3::dot(const Vector3& vector1, const Vector3& vector2) { //: dot product, returns result
	return vector1.m[0] * vector2.m[0] + 
		vector1.m[1] * vector2.m[1] + 
		vector1.m[2] * vector2.m[2];
}


Vector3 Vector3::cross(const Vector3& vector1, const Vector3& vector2) {
	return Vector3(
		vector1.m[1]*vector2.m[2] - vector1.m[2]*vector2.m[1],
		vector1.m[2]*vector2.m[0] - vector1.m[0]*vector2.m[2],
		vector1.m[0]*vector2.m[1] - vector1.m[1]*vector2.m[0]);
}

double Vector3::angleBetween( Vector3& vector1,  Vector3& vector2) {
	double dot = vector1.m[0] * vector2.m[0] +
		vector1.m[1] * vector2.m[1] +
		vector1.m[2] * vector2.m[2];

	double length1 = vector1.length();
	double length2 = vector2.length();

	double angle = dot / (length1 * length2);
	return acos(angle) * 180.0 / M_PI;
}

double Vector3::length() {
	return sqrt(this->m[0]*this->m[0] + this->m[1]*this->m[1] + this->m[2]*this->m[2]);
}

void Vector3::normalize() {
	double length = this->length();
	for (int i = 0; i < Vector3::numElements; i++) {
		this->m[i] = this->m[i] / length;
	}
}

void Vector3::print(std::string& comment) {
	comment.append("m[0]: " + std::to_string(this->m[0]) + ", m[1]: " + std::to_string(this->m[1]) + ", m[2]: " + std::to_string(this->m[2]));
}

std::string Vector3::toString() {
	std::ostringstream ss;
	ss << "x: " << std::to_string(this->m[0]) << ", y: " << std::to_string(this->m[1]) << ", z: " << std::to_string(this->m[2]);
	return ss.str();
}