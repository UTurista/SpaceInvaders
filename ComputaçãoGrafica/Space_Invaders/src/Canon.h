#pragma once
#include <vector>
#include "Collider.h"



/* Canon
 * 
 * 
 * 
*/
class Canon : public Collider{
	//Ofset: Posi��o do Canon no eyxo horizontal -x-
	float _offset;

	//Velocidade do canon
	float _speed;

	//Variaveis para definir a rota��o do Canon
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
	 * >Trocar p'la fun��o GetRightSize() e GetLeftSize()
	*/
	float getLenght();

	/* 
	 * Canon::getOffset()
	 * >Devolve a posi��o do Canon
	*/
	float getOffset();

	/* 
	 * Canon::draw()
	 * >Envia as ordens de desenho para o OpenGl
     * >Nao desenha, ou seja, n�o faz GlFlush()
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
	scale() * >Muda o valor da Posi��o do Canon
	 * >Apenas se verifica altera��es quando o Canon::draw() � chamado
	 * >O novo valor � a adic��o <_speed> com antigo valor <_ofset>
	*/
	void moveRight(float timeCalled);

	/* 
	 * Canon::moveRight()
	 * >Muda o valor da Posi��o do Canon
	 * >Apenas se verifica altera��es quando o Canon::draw() � chamado
	 * >O novo valor � a subtra��o <_speed> com antigo valor <_ofset>
	*/
	void moveLeft(float timeCalled);


	/* 
	 * Canon::setScale()
	 * >Altera a escala do desenho
	*/
	void setScale(int xX, int yY, int zZ){};


	/* 
	 * Canon::setRotation()
	 * >Altera a rota��o do desenho
	*/
	void setRotation(int xX, int yY, int zZ){};





	void weaponFire();

	void tick();





	std::vector<Bullet*> bulletPointer();

	bool colide(Bullet* bullet);

};

