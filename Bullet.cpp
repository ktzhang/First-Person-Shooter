#include "Bullet.h"

#include "Sphere.h"

Bullet::Bullet(){
	radius = 0.01;
	pos = Vector3(0, 0, 0);
}


void Bullet::draw(Matrix4 matrix){
	Sphere *sphere = new Sphere();
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1], pos.m[2]);
	Matrix4 shrink;
	shrink.makeScale(radius, radius, radius);

	bullet = new MatrixTransform(translate * shrink);
	bullet->addChild(sphere);
	bullet->draw(matrix.getPointer());
}