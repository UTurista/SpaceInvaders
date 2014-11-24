
#ifndef _GLUT_H_
#define _GLUT_H_
#include <GL/glut.h>
#endif



enum Mat{	ALIEN_1_CORPO, ALIEN_1_OLHOS,
			ALIEN_2_CORPO, ALIEN_2_OLHOS,
			ALIEN_3_CORPO, ALIEN_3_OLHOS,
			CANON_IN, CANON_OUT,
			BULLET,
			SHIELDS,
			BACKGROUND,
			PARTICLE
};

class Material{

	//Variaveis de um material
	GLfloat mat_ambient[4];
	GLfloat mat_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];
	GLfloat mat_shine;

public:
	Material();
	void setMaterial();
	void editMaterial(float *amb, float *dif, float *espc, float *emiss, float shine);
	int  getMaterial(float *amb, float *dif, float *espc, float *emiss, float shine);
	void resetMaterial();
	void predefMaterial(Mat i);
}; 


