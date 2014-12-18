#include "ParticleEffect.h"
#include "Sphere.h"


ParticleEffect::ParticleEffect(Vector3 pos){
	srand(time(0));
	speed = 0.00095;
	count = 600;
	particles = new vector<Particle*>();
	for (int i = 0; i < count; i++){
		Particle *current = new Particle;
		current->delay = rand() % 4;
		double x = double(2*(rand()%2)-1)*(double)(rand() % 1000) * speed / 1000.0;
		double y = double(2 * (rand() % 2) - 1)*(double)(rand() % 1000) * speed / 1000.0;
		double z = double(2 * (rand() % 2) - 1)*(double)(rand() % 1000) * speed / 1000.0;
		current->dir = Vector3(x, y, z);
		current->pos = pos;
		current->duration = 120 + rand() % 200;
		particles->push_back(current);
	}
}

void ParticleEffect::draw(Matrix4 matrix){
	double s = 0.0010;
	Matrix4 scale;
	scale.makeScale(s,s,s);

	vector<Particle*>::iterator it;
	int active = 0;
	for (it = particles->begin(); it != particles->end(); it++){
		Particle *current = *it;
		if (current->delay <= 0){
			if (current->duration > 0){
				//cout << "Particle effect!!!" << endl;
				current->duration = current->duration - 1;
				current->pos = current->pos + current->dir;
				Sphere *sphere = new Sphere();
				sphere->r = (double)(rand() % 100) / 100.0;
				sphere->g = (double)(rand() % 100) / 100.0;
				sphere->b = (double)(rand() % 100) / 100.0;
				Matrix4 translate;
				translate.makeTranslate(current->pos.m[0], current->pos.m[1], current->pos.m[2]);
				sphere->draw(matrix * translate * scale);
				active++;
				delete sphere;
			}
		}
		else{
			current->delay--;
		}
	}
	//printf("active = %d\n", active);
	if (active == 0) {
		particles->clear();
		alive = false;
	}
}

void ParticleEffect::update(Matrix4 matrix){
	
}

void ParticleEffect::drawBoundingSpheres(Matrix4 worldMatrix){

}