#include "Bullet.h"

const double Bullet::speed = 0.025;

Bullet::Bullet(Vector3 position, Vector3 direction, double l){
	radius = 0.005;
	pos = position;
	dir = direction;
	sphere = new Sphere();
	sphere->r = 0.1;
	sphere->g = 0.08;
	sphere->b = 0.85;
	cylinder = new Cylinder();
	limit = l;
	duration = 100;
}


void Bullet::draw(Matrix4 matrix){
	if (duration <= 0) return;

	updateMotion();
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1], pos.m[2]);
	Matrix4 shrink;
	shrink.makeScale(radius, radius, radius);

	sphere->draw(matrix * translate * shrink);

}

void Bullet::updateMotion(){
	pos.m[0] = pos.m[0] + dir.m[0] * speed;
	pos.m[1] = pos.m[1] + dir.m[1] * speed;
	pos.m[2] = pos.m[2] + dir.m[2] * speed;
	duration--;
}

void Bullet::update(Matrix4 matrix){
}

void Bullet::drawBoundingSpheres(Matrix4 worldMatrix){
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1], pos.m[2]);
	Matrix4 shrink;
	shrink.makeScale(radius, radius, radius);

	sphere->draw(worldMatrix * translate * shrink);
}

int Bullet::getDuration(){
	return duration;
}

void Bullet::render(){}