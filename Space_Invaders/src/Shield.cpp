#include <stdlib.h>
#include "Shield.h"
#include "Alien.h"
#include "Bullet.h"
#include "Material.h"
#include "glut.h"
#include <iostream>

Shield::Shield()
    : pos_x(0)
    , pos_y(0)
{
}

Shield::Shield(float xx, float yy)
{
    pos_x = xx;
    pos_y = yy;
    _mat.predefMaterial(SHIELDS);
    _numlifes = 9;
}

void Shield::draw()
{
    if (life) {
        glColor3f(1.0f, 1.0f, 1.0f); //Definir a cor do Shield

        _mat.setMaterial();

        glPushMatrix();

        glTranslatef(pos_x, pos_y, 0.0); //Preparar todo desenho de acordo com o ofset geral
        glScalef(1, 1, 1); //Possibilidade de escalar
        glRotatef(10, 1, 0, 0);

        //Iniciar o desenho de baixo para cima
        //Base
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 6; i++) {
                glutSolidCube(1);
                glTranslatef(1, 0, 0);
            }

            glTranslatef(4, 0, 0);

            for (int i = 0; i < 6; i++) {
                glutSolidCube(1);
                glTranslatef(1, 0, 0);
            }

            glTranslatef(-16, 1, 0);
        }

        //Centro
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 16; i++) {
                glutSolidCube(1);
                glTranslatef(1, 0, 0);
            }

            glTranslatef(-16, 1, 0);
        }

        //Topo
        glTranslatef(1, 0, 0);
        for (int i = 0; i < 14; i++) {
            glutSolidCube(1);
            glTranslatef(1, 0, 0);
        }
        glTranslatef(-14, 1, 0);

        glTranslatef(1, 0, 0);
        for (int i = 0; i < 12; i++) {
            glutSolidCube(1);
            glTranslatef(1, 0, 0);
        }
        glTranslatef(-12, 1, 0);

        glTranslatef(1, 0, 0);
        for (int i = 0; i < 10; i++) {
            glutSolidCube(1);
            glTranslatef(1, 0, 0);
        }
        glTranslatef(-10, 1, 0);

        glTranslatef(1, 0, 0);
        for (int i = 0; i < 8; i++) {
            glutSolidCube(1);
            glTranslatef(1, 0, 0);
        }
        glPopMatrix();
    }
}

float Shield::getMargin() { return 40; }

bool Shield::colide(Bullet* bullet)
{
    float C1x(bullet->getPosX()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita
    float C1y(bullet->getPosY()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita

    if ((C1x - pos_x) < 18 && (C1x - pos_x) > -3 && C1y < 55 && C1y > 38) {
        float amb[4], dif[4], espc[4], emiss[4], shine(0);

        _mat.getMaterial(amb, dif, espc, emiss, shine);

        if (--_numlifes == 0) {
            life = false;
        }

        // amb[0];
        // amb[1];
        // amb[2];
        // amb[3];

        dif[0] = (rand() % 10) * 0.1;
        dif[1] = (rand() % 10) * 0.1;
        dif[2] = (rand() % 10) * 0.1;
        // dif[3];

        // espc[0];
        // espc[1];
        // espc[2];
        // espc[3];

        // emiss[0];
        // emiss[1];
        // emiss[2];
        // emiss[3];

        _mat.editMaterial(amb, dif, espc, emiss, shine);
        return true;
    }

    return false;
}

bool Shield::colide(Alien* alien)
{
    float C1x(alien->getPosX()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita
    float C1y(alien->getPosY()); //Variaveis desnecessarias, apenas permitem fazer a operação visualmente mais bonita

    if ((C1x - pos_x) < 18 && (C1x - pos_x) > -3 && C1y < 55 && C1y > 38) {
        life = false;
        return true;
    }

    return false;
}

std::vector<Bullet*> Shield::bulletPointer()
{
    std::vector<Bullet*> dontUseIt;
    //FUCKING TERRIBLE HACK
    return dontUseIt;
    //PLEAZE DONT BLAME ME
}