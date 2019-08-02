#pragma once
#include <stdlib.h>
#include "Alien.h"
#include "Background.h"
#include "Camera.h"
#include "Canon.h"
#include "ParticleManager.h"
#include "Shield.h"
#include "glut.h"
#include <sstream>
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

    //Limites do cenário
    const float leftLimit;
    const float rightLimit;

    //Contador de voltas dos aliens
    int alien_counter;

    //Numero de voltas maximo dos aliens
    int alien_maxcounter;

    //Direcção dos Aliens
    bool left;

    //Pontuaçao
    int score;

    //Vidas
    int lives;

public:
    //Constructor com os limites esquerdo e direito;
    GameController(float left, float right);

    //Inicializador do canhão e do aliens
    void init();

    //A função chama todas as funções de desenho de todos os filhos e termina com um glFlush();
    void display();

    //A função controla o contador do numero de voltas que os aliens podem dar ate poderem descer.
    void checkDownMov();

    void GameController::DisplayString(const int x, const int y, const std::string& label, const void* font = (const void*)0) const;

    void HUD();

    //A função tick do GameController é a função chamada de XX em XXmsec. Esta compara a posição relativa da colmeia com os
    //limites laterais e indica a direcção que a colmeia deve tomar.
    void tick();

    /*
	 * São estas as funções que verificam se o canhão pode se deslocar. O teste compara a posição do canhão...//
	 * //...com os limites laterais, caso passe o teste, é chamada a respectia função do canhão.
	*/
    void canonRight(float timeCalled);
    void canonLeft(float timeCalled);

    /*
	 * Camera Update:
	 * >Verifica o valor do Selector de Camera em Uso, e devolve os valors da camera guardada...//
	 * //...nessa posição
	 * >Recebe 9 apontadores para doubles e actualiza-os com os valores para a camera
	 * >Recebe um apontador para bool e actualização com indicação se a camera está ou não em perspectiva
	 */
    void cameraUpdate(double* eyeX, double* eyeY, double* eyeZ,
        double* atX, double* atY, double* atZ,
        double* upX, double* upY, double* upZ, bool* isPerspective);

    //Camera Change: Actualiza o valor da camera em utilização
    void cameraChange(int cam);

    void myLightning();

    void fireWeapon();

    int aliensFireWeapon();

    void colliderManager();

    bool gameOver();
};