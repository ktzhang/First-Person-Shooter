#include "Vector3.h"
#include "math.h"

Vector3 Vector3::operator+(const Vector3& vector) {
	this->x = vector.x + this->x;
	this->y = vector.y + this->y;
	this->z = vector.z + this->z;
	return *this;
}

Vector3 Vector3::operator-(const Vector3& vector) {
	this->x = vector.x - this->x;
	this->y = vector.y - this->y;
	this->z = vector.z - this->z;
	return *this;
}

void Vector3::negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

void Vector3::scale(double s) {
	this->x = this->x * s;
	this->y = this->y * s;
	this->z = this->z * s;
}

double Vector3::dot(const Vector3& vector1, const Vector3& vector2) { //: dot product, returns result
	return vector1.x * vector2.x + 
		vector1.y * vector2.y + 
		vector1.z * vector2.z;
}


Vector3 Vector3::cross(const Vector3& vector1, const Vector3& vector2) {
	return Vector3(
		vector1.y*vector2.z - vector1.z*vector2.y,
		vector1.z*vector2.x - vector1.x*vector2.z,
		vector1.x*vector2.y - vector1.y*vector2.x);
}

double Vector3::length() {
	return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

void Vector3::normalize() {
	double length = this->length();
	this->x = this->x / length;
	this->y = this->y / length;
	this->z = this->z / length;
}

void Vector3::print(std::string& comment) {
	comment.append("x: " + std::to_string(this->x) + ", y: " + std::to_string(this->y) + ", z: " + std::to_string(this->z));
}
