#pragma once
#include "Collider.h"
#include <vector>

class Alien : public Collider {
protected:
    float pos_x; //Posic��o do canto inferior esquerdo no eixo XX
    float pos_y; //Posic��o do canto inferior esquerdo no eixo YY
    bool left; //Direc��o do Alien
    bool _life; //O Alien vive? se True a fun��o Draw deve ser realizada;
    float _lastUpdate;
    float _speed;
    float _lastFire; //Ultima vez que disparou, para evitar Burst rapidos

public:
    std::vector<Bullet*> _bulletsVec;
    Alien(); //Construtor por omiss�o, posic��o inicial 0,0
    Alien(float xx, float yy); //Construtor especifico, posi��o inicial xx,yy
        //Fun��o de desenho

    void moveLeft(); //Alteradores da Posi��o: partilham a variav�l <left>,
    void moveRight(); //quando se alterna de um para o outro avan�a-se uma casa no eixo YY
    void moveDown();
    void fireWeapon();

    float getPosX() { return pos_x; }; //Getters
    float getPosY() { return pos_y; }; //Getters
    bool getLife() { return _life; } //Getters

    void death();
    int draw();
    virtual void design() = 0;
    virtual float getMargin() = 0;

    std::vector<Bullet*> bulletPointer();
    bool colide(Bullet* bullet);
};

/*
	SubClasse Alien #1
*/
class Alien_1 : public Alien {

public:
    Alien_1()
        : Alien() {};
    Alien_1(float xx, float yy)
        : Alien(xx, yy) {};

    void design();
    float getMargin();
};

/*
	SubClasse Alien #2
*/
class Alien_2 : public Alien {

public:
    Alien_2()
        : Alien() {};
    Alien_2(float xx, float yy)
        : Alien(xx, yy) {};

    void design();
    float getMargin();
};

/*
	SubClasse Alien #3
*/
class Alien_3 : public Alien {

public:
    Alien_3()
        : Alien() {};
    Alien_3(float xx, float yy)
        : Alien(xx, yy) {};

    void design();
    float getMargin();
};
