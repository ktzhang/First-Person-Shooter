#include "Robot.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "cube.h"

Robot::Robot()
{
	xPos = 0;
	zPos = 0;
	angle = 0;
	gridPosition = moveRobotMatrix();
	gridPosition->addChild(buildRobot());
}

Robot::Robot(double x, double z, double angle) {
	xPos = x;
	zPos = z;
	this->angle = angle;
	gridPosition = moveRobotMatrix();
	gridPosition->addChild(buildRobot());
}

void Robot::setX(double x) {
	xPos = x;
}

void Robot::setZ(double z) {
	zPos = z;

}

Group* Robot::buildHead() {
	//Robot head
	Matrix4 matrixTranslate = Matrix4();
	matrixTranslate.identity();
	matrixTranslate.makeTranslate(0, 3, 0);
	MatrixTransform* head = new MatrixTransform(matrixTranslate);
	head->addChild(new Sphere());
	return head;
}

Group* Robot::buildTorso() {
	//Robot body
	Matrix4 matrixScale = Matrix4();
	matrixScale.identity();
	matrixScale.makeScale(3, 4, 2);
	MatrixTransform* torso = new MatrixTransform(matrixScale);
	torso->addChild(new Cube());
	return torso;
}


Group* Robot::buildArm(ArmPos armPos) {
	int mult = 1;
	if (armPos == Left) {
		mult = -1;
	}
	double moveAmount = -2.5;
	Matrix4 matrixInitialMove = Matrix4();
	matrixInitialMove.identity();
	matrixInitialMove.makeTranslate(0, -moveAmount, 0);

	Matrix4 rotateMatrix = Matrix4();
	rotateMatrix.identity();
	Vector3 axis = Vector3(1, 0, 0);
	rotateMatrix.makeRotate(angle * mult, axis);

	Matrix4 matrixAfterMove = Matrix4();
	matrixAfterMove.identity();
	matrixAfterMove.makeTranslate(0, moveAmount, 0);


	Matrix4 matrixScale = Matrix4();
	matrixScale.identity();
	matrixScale.makeScale(0.7, 3.5, 1);

	Matrix4 matrixTranslate = Matrix4();
	matrixTranslate.identity();
	matrixTranslate.makeTranslate(mult * 2, 0.2, 0);

	Matrix4 multMatrix = Matrix4();
	multMatrix = matrixInitialMove * rotateMatrix * matrixAfterMove * rotateMatrix * matrixTranslate * matrixScale;

	MatrixTransform* arm = new MatrixTransform(multMatrix);
	arm->addChild(new Cube());
	return arm;
}

Group* Robot::buildLeg(ArmPos armPos) {
	int mult = 1;
	if (armPos == Left) {
		mult = -1;
	}

	double moveAmount = 1.5;

	Matrix4 matrixInitialMove = Matrix4();
	matrixInitialMove.identity();
	matrixInitialMove.makeTranslate(0, -moveAmount, 0);

	Matrix4 rotateMatrix = Matrix4();
	rotateMatrix.identity();
	Vector3 axis = Vector3(1, 0, 0);
	rotateMatrix.makeRotate(angle * mult, axis);

	Matrix4 matrixAfterMove = Matrix4();
	matrixAfterMove.identity();
	matrixAfterMove.makeTranslate(0, moveAmount, 0);

	Matrix4 matrixScale = Matrix4();
	matrixScale.identity();
	matrixScale.makeScale(1, 4.5, 1);

	Matrix4 matrixTranslate = Matrix4();
	matrixTranslate.identity();
	matrixTranslate.makeTranslate(mult * 0.55, -4.7, 0);

	Matrix4 multMatrix = Matrix4();
	multMatrix = matrixInitialMove * rotateMatrix * matrixAfterMove * matrixTranslate * matrixScale;

	MatrixTransform* arm = new MatrixTransform(multMatrix);
	arm->addChild(new Cube());
	return arm;
}


Group* Robot::buildRobot() {
	Group* robot = new Group();
	robot->addChild(buildHead());
	robot->addChild(buildTorso());
	robot->addChild(buildArm(Right));
	robot->addChild(buildArm(Left));
	robot->addChild(buildLeg(Right));
	robot->addChild(buildLeg(Left));
	return robot;
}

MatrixTransform* Robot::moveRobotMatrix() {
	Matrix4 matrixTranslate = Matrix4();
	matrixTranslate.identity();
	matrixTranslate.makeTranslate(xPos, 0, zPos);
		
	MatrixTransform* gridPosition = new MatrixTransform(matrixTranslate);
	return gridPosition;
}

void Robot::setLimbAngle(double angle) {
	this->angle = angle;
}

void Robot::draw(Matrix4 matrix) {
	gridPosition->draw(matrix);
}

void Robot::update(Matrix4 worldMatrix) {
	gridPosition->update(worldMatrix);
}

void Robot::drawBoundingSpheres(Matrix4 worldMatrix) {
	gridPosition->drawBoundingSpheres(worldMatrix);
}


Robot::~Robot()
{


}
