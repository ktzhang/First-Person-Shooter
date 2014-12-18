#include "Bullet.h"

const double Bullet::speed = 0.025;

Bullet::Bullet(Vector3 position, Vector3 direction){
	radius = 0.01;
	pos = position;
	dir = direction;
	sphere = new Sphere();
}


void Bullet::draw(Matrix4 matrix){
	updateMotion();

	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1], pos.m[2]);
	Matrix4 shrink;
	shrink.makeScale(radius, radius, radius);

	bullet = new MatrixTransform(translate * shrink);
	bullet->addChild(sphere);
	bullet->draw(matrix.getPointer());

	delete bullet;
}

void Bullet::updateMotion(){
	pos.m[0] = pos.m[0] + dir.m[0] * speed;
	pos.m[1] = pos.m[1] + dir.m[1] * speed;
	pos.m[2] = pos.m[2] + dir.m[2] * speed;
}

void Bullet::update(Matrix4 matrix){
	bullet->update(matrix);
}

void Bullet::drawBoundingSpheres(Matrix4 worldMatrix){
	bullet->drawBoundingSpheres(worldMatrix);
}