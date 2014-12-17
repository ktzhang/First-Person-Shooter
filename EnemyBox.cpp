#include "EnemyBox.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "cube.h"
#include "TreeObject.h"
#include <cstdlib>


using namespace std;


EnemyBox::EnemyBox() {
	enemy = new Group();
	pos = Vector3(0, 0, 0);
}

EnemyBox::EnemyBox(Vector3 startPos) {
	enemy = new Group();
	pos = startPos;
}

void EnemyBox::prerender() {
	
}

void EnemyBox::draw(Matrix4 matrix) {
	double shrinkFactor = 0.01;
	Cube cube = Cube();
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1] + cube.sideLen / 2, pos.m[2]);
	Matrix4 cubeShrink;
	cubeShrink.makeScale(shrinkFactor, shrinkFactor, shrinkFactor);
	MatrixTransform matrixTransform = MatrixTransform(cubeShrink * translate);
	matrixTransform.addChild(&cube);
	enemy->addChild(&matrixTransform);
	enemy->draw(matrix.getPointer());
}

void EnemyBox::update(Matrix4 worldMatrix) {
	enemy->update(worldMatrix);
}

void EnemyBox::drawBoundingSpheres(Matrix4 worldMatrix) {
	enemy->drawBoundingSpheres(worldMatrix);
}

EnemyBox::~EnemyBox() {
	delete enemy;
}
