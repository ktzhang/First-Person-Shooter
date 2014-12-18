#ifndef PARTICLEEFFECT_H_
#define PARTICLEEFFECT_H_


#include "MatrixTransform.h"
#include "Group.h"
#include "Vector3.h"
#include <cstdlib>
#include <ctime>

class Particle{
public:
	Particle() {}

	int delay;
	Vector3 dir;
	Vector3 pos;
	int duration;
};

class ParticleEffect : public Group{
public:
	ParticleEffect(Vector3);



	Vector3 newPosition();
	virtual void draw(Matrix4 matrix);
	virtual void update(Matrix4 matrix);
	virtual void drawBoundingSpheres(Matrix4 worldMatrix);


	bool alive;
	double duration;
	vector<Particle*> *particles;
	int count;
	double speed;
};


#endif