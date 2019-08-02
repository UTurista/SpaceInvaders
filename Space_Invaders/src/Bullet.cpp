
#include <stdlib.h>
#include "Bullet.h"
#include "glut.h"
#include <cmath>

Bullet::Bullet()
    : _posX(0)
    , _posY(0)
{
}
Bullet::Bullet(float posX, float limit)
    : _speed(0.10)
    , _limit(limit)
    , _posX(posX)
    , _posY(20)
    , _lastUpdate(glutGet(GLUT_ELAPSED_TIME))
    , _draw(true)
{
}
Bullet::Bullet(float posX, float posY, float limit, float speed)
    : _speed(speed)
    , _posY(posY)
    , _limit(limit)
    , _posX(posX)
    , _lastUpdate(glutGet(GLUT_ELAPSED_TIME))
    , _draw(true)
{
}

bool Bullet::isDrawing() { return _draw; }

void Bullet::tick()
{
    float time = glutGet(GLUT_ELAPSED_TIME);

    _posY += _speed * (time - _lastUpdate);
    _lastUpdate = time;

    if (_posY >= _limit) {
        _draw = false;
    } else if (_posY <= -10) {
        _draw = false;
    }
}

void Bullet::resetBullet(float xx, float yy)
{

    _draw = true;
    _posX = xx;
    _posY = yy;
}

void Bullet::draw()
{
    glPushMatrix();
    glTranslatef(_posX, _posY, 0);
    glutSolidSphere(3, 7, 7);
    glPopMatrix();
}
