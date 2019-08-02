
#include "Alien.h"
#include "Bullet.h"
#include "GL\glut.h"
#include "Material.h"
#include <iostream>

#define BURSTFIRE 200

/* Implementação da Super Class -ALIEN-
 *
 *
 *
 */

//Construtor
Alien::Alien()
    : pos_x(0)
    , _life(true)
    , pos_y(0)
    , _speed(0.01)
    , _lastUpdate(glutGet(GLUT_ELAPSED_TIME))
{
}

//Construtor
Alien::Alien(float xx, float yy)
    : _life(true)
    , pos_x(xx)
    , pos_y(yy)
    , _speed(0.01)
    , _lastUpdate(glutGet(GLUT_ELAPSED_TIME))
    , _lastFire(0)
{
}

/* Move Right
 *
 *
 *
 */
void Alien::moveRight()
{
    float time = glutGet(GLUT_ELAPSED_TIME);

    pos_x += _speed * (time - _lastUpdate);
    _lastUpdate = time;
}

/* move Left
 *
 *
 *
 */
void Alien::moveLeft()
{
    float time = glutGet(GLUT_ELAPSED_TIME);

    pos_x -= _speed * (time - _lastUpdate);
    _lastUpdate = time;
}

/* Move Down
 *
 *
 *
 */
void Alien::moveDown()
{
    pos_y -= 1;
}

/* Fire Weapon
 *
 *
 *
 */
void Alien::fireWeapon()
{
    float time = glutGet(GLUT_ELAPSED_TIME);
    if ((time - _lastFire) > BURSTFIRE) {

        bool _new = true;

        std::cout << _bulletsVec.size() << std::endl;

                for
                    each(Bullet * b in _bulletsVec)
                    {
                        if (!(b->isDrawing())) {
                            b->resetBullet(pos_x + 5, pos_y);
                            std::cout << "resetbullet" << std::endl;
                            _new = false;
                            break;
                        }
                    }

                if (_new) {
                    std::cout << "newbullet" << std::endl;
                    Bullet* bullet = new Bullet(pos_x + 5, pos_y, 200, -0.050);
                    _bulletsVec.push_back(bullet);
                }

                _lastFire = glutGet(GLUT_ELAPSED_TIME);
    }
}

/* Death
 *
 *
 *
 */
void Alien::death() { _life = false; }

/* Draw
 *
 *
 *
 */
int Alien::draw()
{
    if (getLife()) {
        design();
    }

    for (int ij = 0; ij < _bulletsVec.size(); ij++) {
        if (_bulletsVec[ij]->isDrawing()) {
            _bulletsVec[ij]->draw();
        }
        _bulletsVec[ij]->tick();
    }

    return 0;
}

std::vector<Bullet*> Alien::bulletPointer()
{
    return _bulletsVec;
}

bool Alien::colide(Bullet* bullet)
{

    float C1x(bullet->getPosX());
    float C1y(bullet->getPosY());

    float distX = C1x - pos_x;
    float distY = C1y - pos_y;

    distX *= distX;
    distY *= distY;
    float dist = distX + distY;

    return (dist < 100);
}

/* Implementação da subClasse ALIEN #1
 *
 */
float Alien_1::getMargin()
{
    //é a distancia para o proximo ser criado, ou seja devolve a soma do comprimento com a margem, cerca de 4
    return 18;
}

void Alien_1::design()
{

    Material mat;
    mat.predefMaterial(ALIEN_1_CORPO);

    int x = 1;

    glColor3f(1.0f, 0.0f, 1.0f); //Definir a cor do Alien_2

    //glLoadIdentity();							//Limpar a matriz, para evitar problemas
    glPushMatrix();
    glScalef(1, 1, 1); //Possibilidade de escalar
    glTranslatef(getPosX(), getPosY(), 0); //Preparar todo desenho de acordo com o ofset geral

    //Corpo
    glScalef(1, 0.9, 1);
    glTranslatef(5, 5, 0);
    glPushMatrix();
    glScalef(5, 5, 5);
    glutSolidCone(1, 1, 3, 3);
    glPopMatrix();

    //1ª linha de esferas
    glPushMatrix();
    glTranslatef(-2, -4, 0);
    glutSolidSphere(1.25, 10, 10);
    glTranslatef(4, 0, 0);
    glutSolidSphere(1.25, 10, 10);

    //2ª linha de esferas
    glTranslatef(-6, -2, 0);
    glutSolidSphere(1.25, 10, 10);
    glTranslatef(4, 0, 0);
    glutSolidSphere(1.25, 10, 10);
    glTranslatef(4, 0, 0);
    glutSolidSphere(1.25, 10, 10);
    glPopMatrix();

    //Olhos
    //glColor3f(0.0f,1.0f,1.0f);

    mat.predefMaterial(ALIEN_1_OLHOS);

    glTranslatef(-1.5, -0.5, 4);
    glutSolidSphere(1, 10, 10);
    glTranslatef(3, 0, 0);
    glutSolidSphere(1, 10, 10);

    glPopMatrix();
}

/*
Implementação da subClasse ALIEN #2
*/
float Alien_2::getMargin()
{
    return 19;
}

void Alien_2::design()
{

    glColor3f(1.0f, 0.5f, 0.0f); //Definir a cor do Alien_2

    Material mat;
    mat.predefMaterial(ALIEN_2_CORPO);

    //glLoadIdentity();							//Limpar a matriz, para evitar problemas
    glPushMatrix();
    glScalef(1, 1, 1); //Possibilidade de escalar
    glTranslatef(getPosX(), getPosY(), 0); //Preparar todo desenho de acorodo com o ofset geral

    glTranslatef(5, 5, 0);
    // Cabeça
    glPushMatrix();
    glScalef(1.1, 0.6, 1);
    glutSolidSphere(4.0, 10.0, 10.0);
    glPopMatrix();

    //Corpo
    glPushMatrix();
    glTranslatef(0, -4, 0);
    glPushMatrix();
    glScalef(1, 1.15, 1);
    glutSolidSphere(2.0, 10.0, 10.0);
    glPopMatrix();

    //Braços e pernas
    glPushMatrix();
    glTranslatef(3, 0.75, 0);
    glutSolidSphere(1.0, 10.0, 10.0);

    glTranslatef(-0.35, -2.5, 0);
    glutSolidSphere(1.0, 10.0, 10.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3, 0.75, 0);
    glutSolidSphere(1.0, 10.0, 10.0);

    glTranslatef(0.35, -2.5, 0);
    glutSolidSphere(1.0, 10.0, 10.0);
    glPopMatrix();
    glPopMatrix();

    //Orelhas
    glPushMatrix();
    glTranslatef(-2.5, 2.4, 0);
    glRotatef(20, 0, 0, 1);
    glScalef(1.2, 1.2, 1.2);
    glutSolidCone(1.0, 1.0, 3.0, 3.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5, 2.4, 0);
    glRotatef(-20, 0, 0, 1);
    glScalef(1.2, 1.2, 1.2);
    glutSolidCone(1.0, 1.0, 3.0, 3.0);
    glPopMatrix();

    //Olhos
    //glColor3f(1.0f,1.0f,0.0f);

    mat.predefMaterial(ALIEN_2_OLHOS);

    glTranslatef(-1.8, 0, 4);
    glutSolidSphere(1.0, 10.0, 10.0);

    glTranslatef(3.6, 0, 0);
    glutSolidSphere(1.0, 10.0, 10.0);

    glPopMatrix();
}

/*
Implementação da subClasse ALIEN #3
*/
float Alien_3::getMargin()
{

    return 18;
}

void Alien_3::design()
{

    glColor3f(0.0f, 1.0f, 0.0f); //Definir a cor do Alien_2

    Material mat;
    mat.predefMaterial(ALIEN_3_CORPO);

    //glLoadIdentity();							//Limpar a matriz, para evitar problemas
    glPushMatrix();
    glScalef(1, 1, 1); //Possibilidade de escalar
    glTranslatef(getPosX(), getPosY(), 0); //Preparar todo desenho de acorodo com o ofset geral

    //Iniciar o desenho de baixo para cima
    //1ª Linha
    glTranslatef(5, 3, 0);
    glScalef(1, 0.7, 1);
    glPushMatrix();
    glutSolidSphere(4.0, 10.0, 10.0);
    glTranslatef(0, 4, 0);
    glPushMatrix();
    glScalef(1, 2, 1);
    glutSolidCube(1);
    glPopMatrix();

    //glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0, 2, 0);
    glutSolidSphere(1.5, 10.0, 10.0);

    //	glColor3f(0.0f, 1.0f, 0.1f);
    glTranslatef(5, -10, 0);
    glutSolidSphere(1.25, 10.0, 10.0);
    glTranslatef(-3, -2, 0);
    glutSolidSphere(1.25, 10.0, 10.0);

    glTranslatef(-4, 0, 0);
    glutSolidSphere(1.25, 10.0, 10.0);
    glTranslatef(-3, 2, 0);
    glutSolidSphere(1.25, 10.0, 10.0);
    glPopMatrix();

    //Olhos
    //glColor3f(0.0f, 0.0f, 1.0f);

    mat.predefMaterial(ALIEN_3_OLHOS);

    glTranslatef(2, 1, 4);
    glutSolidSphere(1.0, 10.0, 10.0);
    glTranslatef(-4, 0, 0);
    glutSolidSphere(1.0, 10.0, 10.0);

    glPopMatrix();
}