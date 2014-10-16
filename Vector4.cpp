#include "Vector4.h"
#include "math.h"
Vector4 Vector4::operator+(const Vector4& vector) {
	for (int i = 0; i < Vector4::numElements; i++){
		this->m[i] = vector.m[i] + this->m[i];
	}
	return *this;
}

Vector4 Vector4::operator-(const Vector4& vector) {
	for (int i = 0; i < Vector4::numElements; i++){
		this->m[i] = vector.m[i] - this->m[i];
	}
	return *this;
}

void Vector4::dehomogenize() {
	for (int i = 0; i < Vector4::numElements-1; i++){
		this->m[i] = this->m[i] / this->m[numElements];
	}
	this->m[numElements] = 1;
}

void Vector4::print(std::string& comment) {
	comment.append("x: " + std::to_string(this->m[0]) + ", y: " + std::to_string(this->m[1]) + ", z: " + std::to_string(this->m[2]) + ", w: " + std::to_string(this->m[3]));
}
