#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <vector>
#endif

#ifndef _BULLET_
#define _BULLET_
#include "Bullet.h"
#endif


class Collider{


public:
	virtual std::vector<Bullet*> bulletPointer()=0;
	virtual bool colide(Bullet* bullet)=0;

};