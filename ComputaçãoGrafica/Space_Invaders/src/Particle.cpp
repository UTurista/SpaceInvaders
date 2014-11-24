#include <iostream>
#include "Particle.h"
/* Construtor por omissão
 * TODO: Convem melhorar algumas inicializações
 */
Particle::Particle(){


}


/* Construtor
 * INPUT: 
 *  >int: timeElapsed		»»» Quando é que a particula foi chamada
 *  >float: px, py, pz		»»» Posição inicial do efeito de particulas, respectivamente no eixo Xx, Yy, Zz
 *	>float: vx, vy, vz		»»» Velocidade inicial das particulas, respectivamente no eixo Xx, Yy, Zz
 *	>float: ax, ay, az		»»» Acelaração das particulas, respectivamente no eixo Xx, Yy, Zz
 */
Particle::Particle(int timeCreated,float px,float py,float pz,float vx, float vy, float vz,float ax,float ay,float az){
	
	_px = px;
	_py = py;
	_pz = pz;

	//A multiplicação serve para reduzir o efeito
	_vx = vx*0.001;
	_vy = vy*0.001;
	_vz = vz*0.001;

	//A multiplicação serve para reduzir o efeito
	_ax = ax*0.0001;
	_ay = ay*0.001;
	_az = az*0.001;
	
	_mat.predefMaterial(PARTICLE);
	
	_timeCreated = timeCreated;
	_lastUpdate = timeCreated;
}

/* Design
 *	>função privada, deve ser tratada pelo draw()
 *	>Trata de todo o design das particulas
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int Particle::design(){

	glPushMatrix();
								
		glTranslatef(_px, _py, _pz);	//Preparar todo desenho de acordo com o ofset geral
		glScalef(.1,.1,.1);	//Possibilidade de escalar

		_mat.setMaterial();
		glutSolidSphere(2,10, 10);

	glPopMatrix();

	return 0;
}


/* Draw
 *	>Fução interface para tratar do design das particulas
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int Particle::draw(){
	if(_life){
		fade();
		design();
	}
	return 0;
}



/* Update
 *	>Actualiza os valores de posição e velocidade
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int Particle::update(){
	float time = glutGet(GLUT_ELAPSED_TIME);
	float delta= (time-_lastUpdate);
	if( (time-_timeCreated)>1500){
		_life=false;
		return 0;
	}


	_px += (_vx * delta);
	_py += (_vy * delta);
	_pz += (_vz * delta);

    _vx += (_ax * delta);
    _vy += (_ay * delta);
    _vz += (_az * delta);
       
	_lastUpdate=time;

	return 0;
}

/* isAlive
 *	>Retorna se a particula está viva
 */
bool Particle::isAlive(){
	return _life;
}


/* Fade
 *	>Pede os valores do material e actualiza-os com novos
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int Particle::fade(){
	float amb[4], dif[4], espc[4], emiss[4], shine(0);
	
	_mat.getMaterial(amb, dif, espc, emiss, shine);

	/*
	amb[0];
	amb[1];
	amb[2];
	amb[3];

	dif[0];
	dif[1];
	dif[2];
	dif[3];

	espc[0];
	espc[1];
	espc[2];
	espc[3];

	emiss[0];
	emiss[1];
	emiss[2];
	emiss[3];
	*/
	amb[0]= amb[0]-0.01;
	
	amb[3]= amb[3]-0.01;

	emiss[0]= emiss[0]-0.01;
	emiss[3] = emiss[3]-0.01;

	_mat.editMaterial(amb, dif, espc, emiss, shine);

	return 0;
}




int Particle::respawn(int timeCreated,float px,float py,float pz,float vx, float vy, float vz,float ax,float ay,float az){
	
	_px = px;
	_py = py;
	_pz = pz;

	//A multiplicação serve para reduzir o efeito
	_vx = vx*0.001;
	_vy = vy*0.001;
	_vz = vz*0.001;

	//A multiplicação serve para reduzir o efeito
	_ax = ax*0.0001;
	_ay = ay*0.001;
	_az = az*0.001;
	
	_mat.predefMaterial(PARTICLE);
	
	_timeCreated = timeCreated;
	_lastUpdate = timeCreated;
	_life=true;

	return 0;
}

