
#ifndef _GLUT_H_
#define _GLUT_H_
#include <GL/glut.h>
#endif

#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Material.h"
#endif



class Particle{
	float _px, _py, _pz;
	float _vx, _vy, _vz;
	float _ax, _ay, _az;
	bool _life;
	float _timeCreated;
	float _lastUpdate;
	Material _mat;

private:	//To clarify these are internal functions
	int design();
	



public:
		Particle();
		Particle(int timeCreated,float px,float py,float pz,float vx, float vy, float vz,float ax,float ay,float az);
	int update();
	int draw();
	int fade();
	bool isAlive();
	int respawn(int timeCreated,float px,float py,float pz,float vx, float vy, float vz,float ax,float ay,float az);
};