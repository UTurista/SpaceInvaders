#include "Canon.h"
#include "Bullet.h"
#include "Material.h"
#include <cmath>
#include <iostream>

#define BURSTFIRE 200

Canon::Canon()
    : _offset(0)
    , _speed(10)
    , _rotation(0)
{
}

void Canon::drawWithVertex()
{

    glBegin(GL_QUADS);
    //Direita
    glNormal3f(1, 0, 0);

    glVertex3f(2, -2, 2);
    glVertex3f(2, -2, -2);
    glVertex3f(2, 2, -2);
    glVertex3f(2, 2, 2);

    //Frente
    glNormal3f(0, 0, 1);

    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    glVertex3f(2, 2, 2);
    glVertex3f(-2, 2, 2);

    //Cima
    glNormal3f(0, 1, 0);

    glVertex3f(-2, 2, 2);
    glVertex3f(2, 2, 2);
    glVertex3f(2, 2, -2);
    glVertex3f(-2, 2, -2);

    //Esquerda
    glNormal3f(-1, 0, 0);

    glVertex3f(-2, 2, 2);
    glVertex3f(-2, 2, -2);
    glVertex3f(-2, -2, -2);
    glVertex3f(-2, -2, 2);

    //Atras
    glNormal3f(0, 0, -1);

    glVertex3f(2, 2, -2);
    glVertex3f(2, -2, -2);
    glVertex3f(-2, -2, -2);
    glVertex3f(-2, 2, -2);

    //Baixo
    glNormal3f(0, -1, 0);

    glVertex3f(2, -2, 2);
    glVertex3f(-2, -2, 2);
    glVertex3f(-2, -2, -2);
    glVertex3f(2, -2, -2);

    glEnd();
}

void Canon::draw()
{

    Material mat;
    mat.predefMaterial(CANON_IN);

    glPushMatrix();
    glScalef(1, 1, 1);
    glTranslatef(_offset, 15, 0);

    glColor3f(1, 0, 1);

    glutSolidSphere(1, 10, 10);

    mat.predefMaterial(CANON_OUT);

    glPushMatrix();
    glColor3f(0, 1, 1);

    glRotatef(45 + _rotation, 0, 1, 0);
    glScalef(0.1, 2, .5);
    glTranslatef(-20, 0, 0);
    //glutSolidCube(4);
    drawWithVertex();

    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);

    glRotatef(135 + _rotation, 0, 1, 0);
    glScalef(0.1, 2, .5);
    glTranslatef(-20, 0, 0);
    //glutSolidCube(4);
    drawWithVertex();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);

    glRotatef(225 + _rotation, 0, 1, 0);
    glScalef(0.1, 2, .5);
    glTranslatef(-20, 0, 0);
    //glutSolidCube(4);
    drawWithVertex();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 1, 1);

    glRotatef(315 + _rotation, 0, 1, 0);
    glScalef(0.1, 2, .5);
    glTranslatef(-20, 0, 0);
    //glutSolidCube(4);
    drawWithVertex();
    glPopMatrix();

    glPopMatrix();

    for (int ij = 0; ij < _bulletsVec.size(); ij++) {
        if ((_bulletsVec[ij]->isDrawing()))
            _bulletsVec[ij]->draw();
    }
}

void Canon::moveRight(float timeCalled)
{
    float time = glutGet(GLUT_ELAPSED_TIME);
    _offset += 2 + 2 * (time - timeCalled);
}

void Canon::moveLeft(float timeCalled)
{
    float time = glutGet(GLUT_ELAPSED_TIME);
    _offset -= 2 - 2 * (time - timeCalled);
}

float Canon::getOffset() { return _offset; }

float Canon::getLenght() { return 4; }

void Canon::weaponFire()
{

    float time = glutGet(GLUT_ELAPSED_TIME);
    if ((time - _lastFire) > BURSTFIRE) {
        bool _new = true;

        std::cout << _bulletsVec.size() << std::endl;

                for
                    each(Bullet * b in _bulletsVec)
                    {
                        if (!(b->isDrawing())) {
                            b->resetBullet(getOffset(), 20);
                            std::cout << "resetbullet" << std::endl;
                            _new = false;
                            break;
                        }
                    }

                if (_new) {
                    std::cout << "newbullet" << std::endl;
                    Bullet* bullet = new Bullet(getOffset(), 200);
                    _bulletsVec.push_back(bullet);
                }

                _lastFire = glutGet(GLUT_ELAPSED_TIME);
    }
}

void Canon::tick()
{
    _rotation += 1;
    for (int ij = 0; ij < _bulletsVec.size(); ij++) {
        _bulletsVec[ij]->tick();
        //if(!_bulletsVec[ij]->isDrawing()){
        //	delete(_bulletsVec[ij]);
        //	_bulletsVec.erase(_bulletsVec.begin()+ij);
        //}
    }
}

std::vector<Bullet*> Canon::bulletPointer()
{
    return _bulletsVec;
}

bool Canon::colide(Bullet* bullet)
{

    float C1x(bullet->getPosX()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita
    float C1y(bullet->getPosY()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita

    if (std::abs(C1x - _offset) < 4 && C1y < 20 && C1y > 0)
        return true;

    return false;
}
