#include "GameController.h"
#include "Bullet.h"
#include <iomanip>
#include <iostream>

//DEFINES
#define PROBABILIDADE 10

GameController::GameController(float left, float right)
    : left(true)
    , leftLimit(left)
    , rightLimit(right)
    , _activeCamera(0)
{
}

/* Init:
 * 
 * 
 * 
*/
void GameController::init()
{

    // Posicionamento inicial dos invaders
    const float XX = -100;
    const float YY = 180;

    //Distancia entre invaders
    float ofset_x = 0;
    float ofset_y = 12;

    //Posicionamento inicial dos shields
    const float XXShields = -67.5;
    const float YYShields = 40;

    //Score inicial
    score = 0;

    //Vidas iniciais
    lives = 3;

    //Inicialização do Canhão do Jogo
    canon = new Canon();

    //Inicialização do Fundo de jogo
    background = new BackGround();

    //Inicialização do contador de voltas dos aliens
    alien_counter = 0;
    //Inicialização do numero maximo de voltas dos aliens
    alien_maxcounter = 1;

    //Inicialização das Cameras
    Camera* camera0 = new Camera(0, 0, 0, 0, 0, 0, 0, 0, 0, false); //Camera Ortogonal
    Camera* camera1 = new Camera(0, 5, 3, 5, 800, 0, 0, 0, 1, true); //Camera na 3ª Pessoa
    Camera* camera2 = new Camera(0, 15, 0, 5, 800, 0, 0, 0, 1, true); //Camera na 1ª Pessoa
    cameras.push_back(camera0);
    cameras.push_back(camera1);
    cameras.push_back(camera2);

    //Inicialização dos Shields
    float yy = YYShields;
    float xx = XXShields;

    for (int i = 0; i < 4; i++) {
        Shield* shield;
        shield = new Shield(xx, yy);
        shields.push_back(shield);
        ofset_x = shield->getMargin();
        xx += ofset_x;
    }

    //Inicialização dos Invaders
    yy = YY;
    xx = XX;
    int debug(0);

    for (int i = 0; i < 10; i++) {
        yy = YY;

        for (int j = 0; j < 6; j++) {
            Alien* ovni;
            switch (j) {
            case 0:
            case 1:
                ovni = new Alien_1((xx), (yy));
                break;
            case 2:
            case 3:
                ovni = new Alien_2(xx, yy);
                break;
            case 4:
            case 5:
                ovni = new Alien_3(xx, yy);
                break;
            }
            //std::cout<<std::setw(2) <<std::setfill('0')<<debug+=6;<<" ";
            invaders.push_back(ovni);
            yy -= ofset_y;
            ofset_x = ovni->getMargin();
        }
        //std::cout<<debug+=i<<std::endl;
        xx += ofset_x;
    }
}

/* Display:
 * 
 * 
 * 
*/
void GameController::display()
{
    HUD();

    background->draw();
    canon->draw();

    for (int i = 0; i < invaders.size(); i++) {
        Alien* ovni = invaders[i];
        ovni->draw();
    }
    for (int i = 0; i < shields.size(); i++) {
        Shield* shield = shields[i];
        shield->draw();
    }

    prtManager.draw();
}

/* Canon Right
 * 
 * 
 * 
*/
void GameController::canonRight(float timeCalled)
{
    if ((canon->getOffset() + canon->getLenght()) < rightLimit) {
        canon->moveRight(timeCalled);
    } //Alem da posição do Canhão é necessario somar a distancia
    //ao ponto mais a direita
}

/* Canon Left
 * 
 * 
 * 
*/
void GameController::canonLeft(float timeCalled)
{
    if (canon->getOffset() - canon->getLenght() > leftLimit) {
        canon->moveLeft(timeCalled);
    } //Alem da posição do Canhão é necessario subtrair a distancia
    //ao ponto mais a esquerda
}

/* Check Down Mov
 * 
 * 
 * 
*/
void GameController::checkDownMov()
{

    if (alien_counter == alien_maxcounter)
        left = !left;
    else {
        alien_counter++;
        left = !left;
    }
}

/* Tick
 * 
 * 
 * 
*/
void GameController::tick()
{
    if (left) {
        Alien* ovni = invaders[0];
        if ((ovni->getPosX() - 1) <= leftLimit) {
            checkDownMov();
        }
    } else {
        Alien* ovni = invaders[59];
        if ((ovni->getPosX() + 12) >= rightLimit) {
            checkDownMov();
        }
    }

    if (alien_counter != alien_maxcounter) { //Se ainda nao chegou ao limite do mumero de voltas, anda normalmente
        for (int i = 0; i < invaders.size(); i++) {
            Alien* ovni = invaders[i];
            if (left) {
                ovni->moveLeft();
            } else {
                ovni->moveRight();
            }
            ovni->draw();
        }
    } else { //Se chegou ao limite do mumero de voltas, desce antes de andar
        for (int i = 0; i < invaders.size(); i++) {
            Alien* ovni = invaders[i];
            if (left) {
                ovni->moveDown();
                ovni->moveLeft();
            } else {
                ovni->moveDown();
                ovni->moveRight();
            }
            ovni->draw();
        }
        alien_counter = 0;
    }

    aliensFireWeapon(); //Algoritmo que gere qual alien dispara
    canon->tick(); //Informa o Canon que passou um tick de tempo
    myLightning(); //Luz é actualizada
    colliderManager();
    prtManager.tick();

    glutPostRedisplay();
}

/* aliensFireWeapon()
 * 
 * 
 * 
*/
int GameController::aliensFireWeapon()
{
    int counter;

    counter = rand() % 60; //Numero aleatorio entre 0-59

    if (!invaders[counter]->getLife()) {
        return 2;
    } //Se o Alien escolhido está 'morto' algoritmo termina

    if (invaders[counter]->getPosY() == invaders[59]->getPosY()) { //Se o Alien escolhido está na ultima linha
        if ((rand() % 50) < PROBABILIDADE) {
            invaders[counter]->fireWeapon();
        }
        return 0;
    }

    /*** Mini algoritmo que verifica se ha aliens em baixo do escolhido ****/
    int x(0);
    bool colunaLivre(true);
    //Enquanto estivermos dentro do intervalo [0-60] e o Proximo Alien se encontra abaixo de Nós
    while (x + counter + 1 < 60 && (invaders[counter + x]->getPosY() > invaders[counter + x + 1]->getPosY())) {
        if (invaders[counter + x + 1]->getLife()) {
            colunaLivre = false;
            break;
        } //Verifica-se se o proximo está morto
        x++;
    }
    /***** *************************************************** ******/

    if (colunaLivre && (rand() % 50) < PROBABILIDADE) //Se a coluna abaixo está vazia ha (1/2) de probabilidade de disparar
        invaders[counter]->fireWeapon();

    return 0;
}

/* Fire Weapon
 * 
 * 
 * 
*/
void GameController::fireWeapon()
{
    canon->weaponFire();
}

/* Camera Change
 * 
 * 
 * 
*/
void GameController::cameraChange(int cam)
{
    std::cout << "Changing camera to " << cam << " " << (cam % cameras.size()) << std::endl;
    _activeCamera = ((cam - 1) % cameras.size()); //A subtração corrige a posição do teclado para o vector.
}

/* Camera Update
 * 
 * 
 * 
*/
void GameController::cameraUpdate(double* eyeX, double* eyeY, double* eyeZ,
    double* atX, double* atY, double* atZ,
    double* upX, double* upY, double* upZ, bool* isPerspective)
{

    double offsets[9];

    Camera* active = cameras[_activeCamera];
    active->getOffsets(offsets);

    //Location of the Camera
    *eyeX = canon->getOffset() + offsets[0];
    *eyeY = offsets[1];
    *eyeZ = offsets[2];

    //Location of the motive
    *atX = canon->getOffset() + offsets[3];
    *atY = offsets[4];
    *atZ = offsets[5];

    //Up vector of the camera
    *upX = offsets[6];
    *upY = offsets[7];
    *upZ = offsets[8];

    *isPerspective = active->getType();
}

/* my Lightning


 */
void GameController::myLightning()
{

    //Luz-0
    //Spot-Light
    //Origem: Canhao, Direcção: eixoYY
    GLfloat diffuse[] = { 1, 1, 1, 1 };
    GLfloat specular[] = { 1, 1, 1, 1 };

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    GLfloat direction[] = { 0, 6, 0.0, 0 };
    GLfloat position[] = { canon->getOffset(), 6, 0, 1 };

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20); // 0~180

    //Luz-1
    //Direcional-Light
    //Origem: __, Direcção: __
    GLfloat diffuse2[] = { .5, .5, .5, 1 };
    GLfloat specular2[] = { .5, .5, .5, 1 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);

    GLfloat direction2[] = { 1, 1, -1, 0 };
    GLfloat position2[] = { -50, -50, 50, 1 };

    glLightfv(GL_LIGHT1, GL_POSITION, direction2);
    glLightfv(GL_LIGHT1, GL_POSITION, position2);
}

/* Collider Managet
 *
 *
 */
void GameController::colliderManager()
{

    //Colector de ponteiros para os vectores de Bullets
    // 0: Canon
    // 1-60: Aliens
    std::vector<Bullet*> allBullets[61];

    allBullets[0] = canon->bulletPointer();
    bool avoidCicle(false);

    // 1º Verificamos as Bullets do Canon
    for (int i = 0; i < allBullets[0].size(); i++) {

        if (!allBullets[0][i]->isDrawing()) {
            continue;
        } //Se a bala não está a ser desenhada nem vale apena continuar, Next!

        for (int j(0); j < shields.size(); j++) {
            if (shields[j]->getLife() && shields[j]->colide(allBullets[0][i])) {
                allBullets[0][i]->death(); //E comeste uma bala
            }
        }

        if (allBullets[0][i]->getPosY() > invaders[59]->getPosY()) { //Apenas se a Bullet se encontra "proxima" da colmeia é que vale apena avançar com colliders detalhados

            for (int j = 0; j < invaders.size(); ++j) { //A todos os Aliens pergunta-se...
                if (invaders[j]->getLife() && invaders[j]->colide(allBullets[0][i])) { //Tas vivo? e Levaste um tiro?
                    invaders[j]->death(); //LOL, então tas morto
                    score++;
                    allBullets[0][i]->death(); //E comeste uma bala (hmm se calhar deveria ser dentro do Alien??)
                    allBullets[j + 1] = invaders[j]->bulletPointer(); //Ja que estamos aqui pede-se as balas do proprio (evita-se um ciclo for no futuro)
                    avoidCicle = true;
                    prtManager.drawAt(invaders[j]->getPosX(), invaders[j]->getPosY(), 0);
                } //Fim do if

                for (int s(0); s < shields.size(); s++) {
                    if (shields[s]->getLife() && shields[s]->colide(invaders[j])) {
                        invaders[j]->death(); //E comeste um alien
                    }
                }

            } //Fim do for

        } //Fim do if
    } //Fim do for, ja todas as balas que o Canon emitiu ja foram testadas à colisão

    if (!avoidCicle) {
        for (int j = 0; j < invaders.size(); j++) { //A todos os Aliens pergunta-se..
            allBullets[j + 1] = invaders[j]->bulletPointer(); //Ja que estamos aqui pede-se as balas do proprio (evita-se um ciclo for no futuro)

            for (int s(0); s < shields.size(); s++) {
                if (shields[s]->getLife() && shields[s]->colide(invaders[j])) {
                    invaders[j]->death(); //E comeste um alien
                }
            }
        }
    } //Fim do if

    //Falta testar todas as balas emitidas por todos os aliens
    for (int i = 1; i <= 60; ++i) {
        for (int j = 0; j < allBullets[i].size(); j++) {
            if (!allBullets[i][j]->isDrawing()) {
                continue;
            } //Se a bala não está a ser desenhada nem vale apena continuar, Next!

            for (int s(0); s < shields.size(); s++) {
                if (shields[s]->getLife() && shields[s]->colide(allBullets[i][j])) {
                    allBullets[i][j]->death(); //E comeste uma bala
                }
            }

            if (allBullets[i][j]->getPosY() < 20) { //Apenas se a Bullet se encontra "proxima" do Canon é que vale apena avançar com colliders detalhados
                if (canon->colide(allBullets[i][j])) {
                    gameOver();
                    allBullets[i][j]->death();
                    prtManager.drawAt(canon->getOffset() - 6, 10, 0);
                };
            }
        }
    }
}

/* Game Over
 *
 *
 */
bool GameController::gameOver()
{

    //more complicated code
    lives--;
    return true;
}

/* display String
 *
 *
 */
void GameController::DisplayString(const int x, const int y, const std::string& label, const void* font) const
{
    void* fontToUse = (font != NULL) ? (void*)font : GLUT_BITMAP_HELVETICA_12;
    glRasterPos2i(x, y);
    for (int i = 0; i < label.size(); i++)
        glutBitmapCharacter(fontToUse, label[i]);
}

/* HUD
 *
 *
 */
void GameController::HUD()
{
    // Switch to raster mode (saving active projection)
    glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0., 1., 0.);
    Material mat;
    mat.predefMaterial(ALIEN_2_OLHOS);
    //DisplayString( 5, 5, CommandLabel);

    std::ostringstream _score;
    std::ostringstream _lives;
    _score << "Score: " << score;
    DisplayString(5, glutGet(GLUT_WINDOW_HEIGHT) - 20, _score.str(), GLUT_BITMAP_HELVETICA_18);
    _lives << "Lives: " << lives;
    DisplayString(glutGet(GLUT_WINDOW_WIDTH) - 100, glutGet(GLUT_WINDOW_HEIGHT) - 20, _lives.str(), GLUT_BITMAP_HELVETICA_18);

    // Switch back to normal mode (restoring projection)
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
}
