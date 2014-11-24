#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#include "Collider.h"
#endif
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#include "Material.h"
#endif
#ifndef _ALIEN_H_
#define _ALIEN_H_
#include "Alien.h"
#endif



class Shield: public Collider{
	float pos_x;	//Posicção do canto inferior esquerdo no eixo XX
	float pos_y;	//Posicção do canto inferior esquerdo no eixo YY
	bool life;		//O Shield vive? se True a função Draw deve ser realizada;
	int	_numlifes;	//Number of lifes
	Material _mat;

public:
	Shield();						//Construtor por omissão, posicção inicial 0,0
	Shield(float xx, float yy);		//Construtor especifico, posição inicial xx,yy
		//Função de desenho


	float getPosX(){return pos_x;};	//Getters
	float getPosY(){return pos_y;};	//Getters
	bool getLife(){return life;}	//Getters

	void draw();	
	float getMargin();
	

	std::vector<Bullet*> bulletPointer();
	bool colide(Bullet* bullet);
	bool colide(Alien* alien);
};