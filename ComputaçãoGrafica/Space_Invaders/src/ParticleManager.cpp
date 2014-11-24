#include "ParticleManager.h"
#define EFFECT 250

/* Construtor por omissão
 * TODO: Convem melhorar algumas inicializações
 */
ParticleManager::ParticleManager(){}


/* drawAt
 *	>Não é o melhor nome;
 *	>Faz um request de um efeito numa dada posição
 *	>Defini-se como um efeito um conjunto de <EFFECT> particulas;
 *	>TODO: Tratar da Memory Leak
 *	>TODO: Verificar se existe já em memoria particulas prontas (isAlive=false) e chamar essas em vez de allocar novas
 *	>TODO: Paz no mundo
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int ParticleManager::drawAt(float px, float py, float pz){
	std::cout<<"ParticleManager::drawAt"<<std::endl<<" -INPUT: "<<px<<" "<<py<<" "<<pz<<std::endl;

	bool _new = true;
	int counter(0);
	float vx, vy, vz, ax, ay, az;
	std::vector<Particle*>::iterator it = _ParticleVec.begin();

	std::cout<<"ParticleManager::drawAt"<<"Currently there's "<< _ParticleVec.size()<<" particles = "<<_ParticleVec.size()/EFFECT<<" Effects"<<std::endl;
	while(it != _ParticleVec.end() && counter<=EFFECT){
		

		if((*it)->isAlive()){
			std::cout<<"ParticleManager::drawAt"<<"Effect is Alive going for the next"<<std::endl;
			it+=EFFECT;
			continue;
		}

			valuesGenerator(&px, &py,&pz, &vx, &vy, &vz, &ax, &ay, &az);
			float time = glutGet(GLUT_ELAPSED_TIME);
			(*it)->respawn(
					time,
					px+6,py+5,pz,
					vx,vy,vz,
					ax,ay,az);
			counter++;
			it++;
			_new=false;
	}

	counter=0;

	if(_new){
		std::cout<<"ParticleManager::drawAt"<<"No available Effects found, creating more"<<std::endl;
		while(counter != EFFECT){

			valuesGenerator(&px, &py,&pz, &vx, &vy, &vz, &ax, &ay, &az);
			float time = glutGet(GLUT_ELAPSED_TIME);

			_ParticleVec.push_back(
				new Particle(
					time,
					px+6,py+5,pz,
					vx,vy,vz,
					ax,ay,az));
			//std::cout<<"creating Particle "<<counter+1<<" of "<<EFFECT<<std::endl;
			counter++;
		}
	}

	return 0;
}

/* Draw
 *	>Percorre o vector e manda desenhar todas as particulas
 *	>TODO: Verificar se a particula precisa de ser desenhada (isAlive)
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int ParticleManager::draw(){
	std::vector<Particle*>::iterator it = _ParticleVec.begin();

	while(it != _ParticleVec.end()){
		(*it)->draw();
		it++;
	}

	return 0;

}


/* tick
 *	>Fução periodica
 *	>Percorre o vector e manda actualizar todas as particulas
 *	>TODO: Verificar se a particula precisa de ser actualizada
 * RETURN:
 *	 0:	bem sucedido
 *  -1:	mal sucedido
 */
int ParticleManager::tick(){
	std::vector<Particle*>::iterator it = _ParticleVec.begin();

	while(it != _ParticleVec.end()){
		(*it)->update();
		it++;
	}
	return 0;
}




int ParticleManager::valuesGenerator(float *px,float *py,float *pz,float *vx, float *vy, float *vz,float *ax,float *ay,float *az){
			double v = 0.8*rand()+0.2;
			if(v>50)v=10;
			double phi = rand()*3.14;
			double theta = 2.0*rand()*3.14;

			*vx = v * cos(theta) * sin(phi);
			*vy = v * cos(phi);
			*vz = v * sin(theta) * sin(phi);
			*ax =  0.01f; /* just a little wind */
			*ay = -0.15f; /* gravity pull */
			*az =  0.00f;
	return 0;
}