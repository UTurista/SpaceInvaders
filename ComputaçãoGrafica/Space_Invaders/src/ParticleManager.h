#pragma once
#include <vector>

class Particle;

class ParticleManager{
	std::vector<Particle*> _ParticleVec;
	Particle* asd;

private:
	int valuesGenerator(float *px,float *py,float *pz,float *vx, float *vy, float *vz,float *ax,float *ay,float *az);

public:
	ParticleManager();
	int tick();
	int drawAt(float px,float  py,float pz);
	int draw();
};