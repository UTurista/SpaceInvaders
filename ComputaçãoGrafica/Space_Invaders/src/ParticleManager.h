#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_
#include <iostream>
#endif
#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <vector>
#endif
#include <random>
#include "Particle.h"
class ParticleManager{
	std::vector<Particle*> _ParticleVec;

private:
	int valuesGenerator(float *px,float *py,float *pz,float *vx, float *vy, float *vz,float *ax,float *ay,float *az);
public:
	ParticleManager();
	int tick();
	int drawAt(float px,float  py,float pz);
	int draw();

};