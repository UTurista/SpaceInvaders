#pragma once
#include "Alien.h"
#include "Background.h"
#include "Camera.h"
#include "Canon.h"
#include "ParticleManager.h"
#include "Shield.h"
#include <GL/glut.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

class GameController {
    Canon* canon; //Canon -Jogador-
    BackGround* background; //Fundo do jogo
    std::vector<Alien*> invaders; //Aliens
    std::vector<Shield*> shields; //Shields
    std::vector<Camera*> cameras; //Cameras
    int _activeCamera; //Selector da camera em Uso
    ParticleManager prtManager;

    //Limites do cen�rio
    const float leftLimit;
    const float rightLimit;

    //Contador de voltas dos aliens
    int alien_counter;

    //Numero de voltas maximo dos aliens
    int alien_maxcounter;

    //Direc��o dos Aliens
    bool left;

    //Pontua�ao
    int score;

    //Vidas
    int lives;

public:
    //Constructor com os limites esquerdo e direito;
    GameController(float left, float right);

    //Inicializador do canh�o e do aliens
    void init();

    //A fun��o chama todas as fun��es de desenho de todos os filhos e termina com um glFlush();
    void display();

    //A fun��o controla o contador do numero de voltas que os aliens podem dar ate poderem descer.
    void checkDownMov();

    void GameController::DisplayString(const int x, const int y, const std::string& label, const void* font = (const void*)0) const;

    void HUD();

    //A fun��o tick do GameController � a fun��o chamada de XX em XXmsec. Esta compara a posi��o relativa da colmeia com os
    //limites laterais e indica a direc��o que a colmeia deve tomar.
    void tick();

    /*
	 * S�o estas as fun��es que verificam se o canh�o pode se deslocar. O teste compara a posi��o do canh�o...//
	 * //...com os limites laterais, caso passe o teste, � chamada a respectia fun��o do canh�o.
	*/
    void canonRight(float timeCalled);
    void canonLeft(float timeCalled);

    /*
	 * Camera Update:
	 * >Verifica o valor do Selector de Camera em Uso, e devolve os valors da camera guardada...//
	 * //...nessa posi��o
	 * >Recebe 9 apontadores para doubles e actualiza-os com os valores para a camera
	 * >Recebe um apontador para bool e actualiza��o com indica��o se a camera est� ou n�o em perspectiva
	 */
    void cameraUpdate(double* eyeX, double* eyeY, double* eyeZ,
        double* atX, double* atY, double* atZ,
        double* upX, double* upY, double* upZ, bool* isPerspective);

    //Camera Change: Actualiza o valor da camera em utiliza��o
    void cameraChange(int cam);

    void myLightning();

    void fireWeapon();

    int aliensFireWeapon();

    void colliderManager();

    bool gameOver();
};