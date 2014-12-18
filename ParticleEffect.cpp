#include "ParticleEffect.h"
#include "Sphere.h"


ParticleEffect::ParticleEffect(){
	srand(time(0));
	speed = 0.1;
	count = 50;
	particles = new vector<Particle*>();
	for (int i = 0; i < count; i++){
		Particle *current = new Particle;
		current->delay = rand() % 12;
		double x = (double)(rand() % 1000) * speed / 1000.0;
		double y = (double)(rand() % 1000) * speed / 1000.0;
		double z = (double)(rand() % 1000) * speed / 1000.0;
		current->dir = Vector3(x, y, z);
		current->pos = Vector3(0, 0, 0);
		current->duration = 30;
		particles->push_back(current);
	}
}

void ParticleEffect::draw(Matrix4 matrix){
	double s = 0.01;
	Matrix4 scale;
	scale.makeScale(s,s,s);

	vector<Particle*>::iterator it;
	int active = 0;
	for (it = particles->begin(); it != particles->end(); it++){
		Particle *current = *it;
		//if (current.delay <= 0){
		current->duration = current->duration - 1;
			current->pos = current->pos + current->dir;
			Sphere *sphere = new Sphere();
			Matrix4 translate;
			translate.makeTranslate(current->pos.m[0], current->pos.m[1], current->pos.m[2]);
			MatrixTransform *part;
			part = new MatrixTransform(translate * scale);
			part->addChild(sphere);
			part->draw(matrix.getPointer());
			if (current->duration > 0) active++;
			delete sphere;
			delete part;
		//}
		//else{
		//	current.delay--;
		//}
	}
	//printf("active = %d\n", active);
	if (active == 0) particles->clear();
}

void ParticleEffect::update(Matrix4 matrix){
	
}

void ParticleEffect::drawBoundingSpheres(Matrix4 worldMatrix){

}