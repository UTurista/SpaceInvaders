#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_
#include <iostream>
#endif
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Material.h"
#endif





Material::Material(){};


//Funçao que actualiza as componentes do material
void Material::editMaterial(float *amb, float *dif, float *espc, float *emiss, float shine){

	mat_ambient[0] = amb[0];
	mat_ambient[1] = amb[1];
	mat_ambient[2] = amb[2];
	mat_ambient[3] = amb[3];

	mat_diffuse[0] = dif[0];
	mat_diffuse[1] = dif[1];
	mat_diffuse[2] = dif[2];
	mat_diffuse[3] = dif[3];

	mat_specular[0] = espc[0];
	mat_specular[1] = espc[1];
	mat_specular[2] = espc[2];
	mat_specular[3] = espc[3];

	mat_emission[0] = emiss[0];
	mat_emission[1] = emiss[1];
	mat_emission[2] = emiss[2];
	mat_emission[3] = emiss[3];

	mat_shine = shine;

	}


int Material::getMaterial(float *amb, float *dif, float *espc, float *emiss, float shine){

	amb[0] = mat_ambient[0];
	amb[1] = mat_ambient[1];
	amb[2] = mat_ambient[2];
	amb[3] = mat_ambient[3];

	dif[0] = mat_diffuse[0];
	dif[1] = mat_diffuse[1];
	dif[2] = mat_diffuse[2];
	dif[3] = mat_diffuse[3];

	espc[0] = mat_specular[0];
	espc[1] = mat_specular[1];
	espc[2] = mat_specular[2];
	espc[3] = mat_specular[3];

	emiss[0] = mat_emission[0];
	emiss[1] = mat_emission[1];
	emiss[2] = mat_emission[2];
	emiss[3] = mat_emission[3];

	shine = mat_shine;

	return 0;
	}


void Material::setMaterial() {

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv (GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shine);

}


void Material::resetMaterial(){
	GLfloat reset[] = {1, 1, 1, 1};
	editMaterial(reset, reset, reset, reset, 0);
}

void Material::predefMaterial(Mat mat){
	GLfloat amb[4];
	GLfloat dif[4];
	GLfloat espc[4];
	GLfloat emiss[4];
	GLfloat shine(0);
	switch (mat){
		case ALIEN_1_CORPO:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.7; 	dif[1]=0.0;		dif[2]=0.7;		dif[3]=1;
				espc[0]=0.7; 	espc[1]=0.0;	espc[2]=0.7;	espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0;
				shine	= 10.0;
			break;

		case ALIEN_1_OLHOS:		
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.7; 	dif[1]=0.0;		dif[2]=0.7;		dif[3]=1;
				espc[0]=0.7; 	espc[1]=0.0;	espc[2]=0.7;	espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.7;	emiss[2]=0.7;	emiss[3]=1;
				shine	= 10.0;
			break;

	case ALIEN_2_CORPO:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.7; 	dif[1]=0.2;		dif[2]=0.0;		dif[3]=1;
				espc[0]=0.7; 	espc[1]=0.2;	espc[2]=0.0;	espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0.0;
				shine	= 10.0;
				break;


	case ALIEN_2_OLHOS:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.7; 	dif[1]=0.2;		dif[2]=0.0;		dif[3]=1;
				espc[0]=0.7; 	espc[1]=0.2;	espc[2]=0.0;	espc[3]=1;
				emiss[0]=0.7; 	emiss[1]=0.7;	emiss[2]=0.0;	emiss[3]=1;
				shine	= 10.0;
				break;


	case ALIEN_3_CORPO:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.0; 	dif[1]=0.5;		dif[2]=0.0;		dif[3]=0.2;
				espc[0]=0.0; 	espc[1]=0.5;	espc[2]=0.0;	espc[3]=0.2;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0;
				shine	= 10.0;
				break;


	case ALIEN_3_OLHOS:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.0; 	dif[1]=0.5;		dif[2]=0.0;		dif[3]=0.2;
				espc[0]=0.0; 	espc[1]=0.5;	espc[2]=0.0;	espc[3]=0.2;
				emiss[0]=0.5; 	emiss[1]=0.0;	emiss[2]=0.5;	emiss[3]=1;
				shine	= 10.0;
			break;


	case CANON_IN:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.25; 	dif[1]=0.0;		dif[2]=0.25;		dif[3]=1;
				espc[0]=0.7; 	espc[1]=0.0;	espc[2]=0.7;	espc[3]=1;
				emiss[0]=0.25; 	emiss[1]=0.0;	emiss[2]=0.25;	emiss[3]=1;
				shine	= 50.0;
			break;


	case CANON_OUT:
				amb[0]=0.25; 	amb[1]=0.25;		amb[2]=0.25;		amb[3]=1;
				dif[0]=0.0; 	dif[1]=1.0;		dif[2]=1.0;		dif[3]=1;
				espc[0]=0.0; 	espc[1]=1.0;	espc[2]=1.0;	espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0;
				shine	= 50.0;
			break;


	case SHIELDS:
				amb[0]=1.0; 	amb[1]=0.0;		amb[2]=0.0;		amb[3]=1;
				dif[0]=1.0; 	dif[1]=0.0;		dif[2]=0.0;		dif[3]=1;
				espc[0]=1.0; 	espc[1]=0.0;	espc[2]=0.0;	espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0;
				shine	= 10.0;
			break;

	case BULLET:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=0.5; 	dif[1]=0.5;		dif[2]=0.5;		dif[3]=1;
				espc[0]=0.5; 	espc[1]=0.5;	espc[2]=0.5;	espc[3]=1;
				emiss[0]=0.5; 	emiss[1]=0.5;	emiss[2]=0.5;	emiss[3]=1;
				shine	= 10.0;
			break;

	case BACKGROUND:
				amb[0]=0.5; 	amb[1]=0.5;		amb[2]=0.5;		amb[3]=1;
				dif[0]=1.0; 	dif[1]=1.0;		dif[2]=1.0;		dif[3]=1.0;
				espc[0]=.5; 	espc[1]=.5;		espc[2]=.5;		espc[3]=1;
				emiss[0]=0.0; 	emiss[1]=0.0;	emiss[2]=0.0;	emiss[3]=0;
				shine	= 13.0;
			break;
	case PARTICLE:
				amb[0]=(rand()%10)*0.1;		amb[1]=0;		amb[2]=0;		amb[3]=1;
				dif[0]=0;					dif[1]=0;		dif[2]=0;		dif[3]=0;
				espc[0]=0;					espc[1]=0;		espc[2]=0;		espc[3]=0;
				emiss[0]=(rand()%10)*0.1;	emiss[1]=0;		emiss[2]=0;		emiss[3]=1;
				shine	= 10.0;
			break;

	}
	editMaterial(amb, dif, espc, emiss, shine);
	setMaterial();
}
