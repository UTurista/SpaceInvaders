#pragma once
#include <vector>
#include "Collider.h"



/* Canon
 * 
 * 
 * 
*/
class Canon : public Collider{
	//Ofset: Posição do Canon no eyxo horizontal -x-
	float _offset;

	//Velocidade do canon
	float _speed;

	//Variaveis para definir a rotação do Canon
	float _rotation;
	
	//Variaveis para definir a escala do Canon
	float* _scale;

	std::vector<Bullet*> _bulletsVec;	//

	float _lastFire;	//Ultima vez que disparou, para evitar Burst rapidos
	

public:
	/* Canon::Canon()
	 * >Construtor do Canon;
	*/
	Canon();

	/* 
	 * Canon::getLenght()
	 * >Trocar p'la função GetRightSize() e GetLeftSize()
	*/
	float getLenght();

	/* 
	 * Canon::getOffset()
	 * >Devolve a posição do Canon
	*/
	float getOffset();

	/* 
	 * Canon::draw()
	 * >Envia as ordens de desenho para o OpenGl
     * >Nao desenha, ou seja, não faz GlFlush()
	*/
	void draw();

	/* 
	 * Canon::drawWithVertex()
	 * >Constroi um solido a partir de vertices e normais
     * 
	*/
	void drawWithVertex();

	/* 
	 * Canon::moveRight()
	scale() * >Muda o valor da Posição do Canon
	 * >Apenas se verifica alterações quando o Canon::draw() é chamado
	 * >O novo valor é a adicção <_speed> com antigo valor <_ofset>
	*/
	void moveRight(float timeCalled);

	/* 
	 * Canon::moveRight()
	 * >Muda o valor da Posição do Canon
	 * >Apenas se verifica alterações quando o Canon::draw() é chamado
	 * >O novo valor é a subtração <_speed> com antigo valor <_ofset>
	*/
	void moveLeft(float timeCalled);


	/* 
	 * Canon::setScale()
	 * >Altera a escala do desenho
	*/
	void setScale(int xX, int yY, int zZ){};


	/* 
	 * Canon::setRotation()
	 * >Altera a rotação do desenho
	*/
	void setRotation(int xX, int yY, int zZ){};





	void weaponFire();

	void tick();





	std::vector<Bullet*> bulletPointer();

	bool colide(Bullet* bullet);

};

