#pragma once
#include "MatrixTransform.h"
#include "Group.h"


class Robot :
	public Group
{
	double xPos;
	double zPos;
	double angle;
	MatrixTransform* gridPosition;

private:
	Group* buildHead();
	Group* buildTorso();
	Group* buildRobot();

	enum ArmPos { Left, Right };
	Group* buildArm(ArmPos armPos);
	Group* buildLeg(ArmPos armPos);

	MatrixTransform* moveRobotMatrix();

public:
	Robot();
	Robot::Robot(double x, double z, double angle);
	void setX(double x);
	void setZ(double z);
	void setLimbAngle(double angle);

	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);
	~Robot();
};

