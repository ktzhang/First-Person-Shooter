#include "EnemyBox.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "cube.h"
#include "TreeObject.h"
#include <cstdlib>


using namespace std;


EnemyBox::EnemyBox() {
	/*Matrix4 identity;
	identity.identity();
	enemy = new MatrixTransform(identity);*/
	sidelen = Cube::SIDELEN * shrinkFactor;

	pos = Vector3(0, 0, 0);
}

EnemyBox::EnemyBox(Vector3 startPos) {
	//Matrix4 identity;
	//identity.identity();
	//enemy = new MatrixTransform(identity);
	sidelen = Cube::SIDELEN * shrinkFactor;

	pos = startPos;
}

void EnemyBox::prerender() {
}

void EnemyBox::draw(Matrix4 matrix) {
	Cube* cube =  new Cube();
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1] , pos.m[2]);
	Matrix4 cubeShrink;
	cubeShrink.makeScale(shrinkFactor, shrinkFactor, shrinkFactor);


	enemy = new MatrixTransform(translate * cubeShrink);
	enemy->addChild(cube);
	//enemy->addChild(&matrixTransform);
	enemy->draw(matrix.getPointer());
}

void EnemyBox::update(Matrix4 worldMatrix) {
	enemy->update(worldMatrix);
}

void EnemyBox::drawBoundingSpheres(Matrix4 worldMatrix) {
	enemy->drawBoundingSpheres(worldMatrix);
}

EnemyBox::~EnemyBox() {
	if (enemy != nullptr) {
//		delete enemy;
	}
}
