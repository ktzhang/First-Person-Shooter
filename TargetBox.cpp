#include "TargetBox.h"

#include "cube.h"


TargetBox::TargetBox(Vector3 position, Vector3 direction, double s, double l){
	pos = position;
	dir = direction;

	scale = s;
	limit = l - scale / 2;
	speed = 0.004;
	cube = new Sphere();

	px = pos.m[0];
	py = pos.m[1];
	pz = pos.m[2];

	dx = dir.m[0];
	dy = dir.m[1];
	dz = dir.m[2];
	//cout << "pos[0] = " << pos.m[0] << "    pos[1] = " << pos.m[1] << "    pos[2] = " << pos.m[2] << endl;
	//cout << "dir[0] = " << dir.m[0] << "    dir[1] = " << dir.m[1] << "    dir[2] = " << dir.m[2] << endl;
}


void TargetBox::draw(Matrix4 matrix){
	updatePosition();
	Matrix4 translate;
	translate.makeTranslate(px,py,pz);
	Matrix4 shrink;
	shrink.makeScale(scale, scale, scale);
	cube->draw(matrix * translate * shrink);
}


void TargetBox::updatePosition(){
	double x = px + dx * speed;
	double y = py + dy * speed;
	double z = pz + dz * speed;

	if (x < -limit || x > limit){
		dx = 0-dx;
	}
	if (y < 0.01 || y > limit){
		dy = -dy;
	}
	if (z < -limit || z > limit){
		dz = -dz;
	}

	px = px + dx * speed;
	py = py + dy * speed;
	pz = pz + dz * speed;
}

void TargetBox::update(Matrix4 aa){}

void TargetBox::drawBoundingSpheres(Matrix4 aa){
	Matrix4 translate;
	translate.makeTranslate(px, py, pz);
	Matrix4 shrink;
	shrink.makeScale(scale, scale, scale);
	cube->drawBoundingSpheres(aa  * translate * shrink);
}

void TargetBox::render(){}