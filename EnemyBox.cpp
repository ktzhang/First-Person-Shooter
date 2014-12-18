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
	sideLen = Cube::SIDELEN * shrinkFactor;
	pos = Vector3(0, 0, 0);
	moveDirection = Vector3(1, 0, 0);
	speed = 0.005;
}

EnemyBox::EnemyBox(Vector3 startPos, Vector3 direction, double speed) {
	//Matrix4 identity;
	//identity.identity();
	//enemy = new MatrixTransform(identity);
	sideLen = Cube::SIDELEN * shrinkFactor;
	pos = startPos;
	this->moveDirection = direction;
	this->speed = speed;
}

void EnemyBox::prerender() {
}

Vector3 EnemyBox::newPosition() {
	Vector3 newPos = pos + Vector3(moveDirection.m[0] * speed, moveDirection.m[1] * speed, moveDirection.m[2] * speed);
	return newPos;
}

void EnemyBox::draw(Matrix4 matrix) {
	Cube* cube =  new Cube();
	Matrix4 translate;
	translate.makeTranslate(pos.m[0], pos.m[1], pos.m[2]);
	Matrix4 cubeShrink;
	cubeShrink.makeScale(shrinkFactor, shrinkFactor, shrinkFactor);
	enemy = new MatrixTransform(translate * cubeShrink);
	enemy->addChild(cube);
	//enemy->addChild(&matrixTransform);
	enemy->draw(matrix.getPointer());


	///Caclculating bounding box
	double botX = pos.m[0] - sideLen / 2;
	double botY = pos.m[1] - sideLen / 2;
	double botZ = pos.m[2] - sideLen / 2;
	boundingBoxMinMax[0] = Vector3(botX, botY, botZ);

	double newX, newY, newZ;
	newX = botX + sideLen;
	newY = botY + sideLen;
	newZ = botZ + sideLen;
	boundingBoxMinMax[1] = Vector3(newX, newY, newZ);
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
