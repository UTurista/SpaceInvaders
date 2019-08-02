#pragma once
#include <vector>

class Bullet;

class Collider{


public:
	virtual std::vector<Bullet*> bulletPointer()=0;
	virtual bool colide(Bullet* bullet)=0;

};