//Includes
#include <string>
#include "src/GameController.h"
#include "src/SpaceInvaders.h"



//Space Invaders Constants
const int TIMER= 5; //em msec
const float LEFT_WALL	= -100;
const float RIGHT_WALL	=  100;
const float HEIGHT		=  200;

//GameController of SpaceInvaders
GameController *game;


GLfloat amb[] = {.1, .1, .1, 1};


/* My Display:
 * >Limpa o color Buffer e DepthBuffer.
 * >Chama o gestor de Camaras
 * >Prepara o Z-Buffer
 * >Chama o Desenhador do GameControler
 * >"Imprime" o desenho -GlFlush()-
 *
 * Problemas:
 * >Diria que os Enables poderiam ser chamados apenas uma vez mas/
aparentemente tenho de chamar constantemente
 *
*/
void myDisplay(void) {

	//'Reset' ao Ecrã
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//'Reset' ao Z-buffer
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Gestor de Camaras
	myCamera();


	//Gestor do Desenho
	game->display();
	
	//Flush das Instruções de Desenho
	glFlush();
}




void myIlumination(){
	GLfloat amb_temp[] = {0, 0, 0, 0};
	switch (ilumination){
	//case 0: break;			//Caso 0 está inserido no Default
								//Alternativa a este switch/Case seria criar um objecto com estado interno
	case 1: glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb);
			glDisable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			ilumination=0;
			break;
	default:glLightModelfv(GL_LIGHT_MODEL_AMBIENT,amb_temp);
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			ilumination=1;
	}
	
}




/* My Camera:
 * 
 * 
 * 
*/
void myCamera(){
	double eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ; 
	bool perspective;

	game->cameraUpdate(&eyeX , &eyeY, &eyeZ, &atX, &atY, &atZ, &upX, &upY, &upZ, &perspective);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(perspective){
		gluPerspective(60, 1,1, 1000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
	}else{
		glOrtho(LEFT_WALL, RIGHT_WALL, 0.0f, HEIGHT, -7.0f, 7.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}	
		
}




/* My Reshape:
 * 
 * 
 * 
*/
void myReshape(GLsizei w, GLsizei h) {
		int z= min(w, h);
		glViewport((w-z)/2, (h-z)/2, z, z);
}





/* My Input:
 * 
 * 
 * 
*/
void myInput(unsigned char key, int x, int y){
	if(key-'a'==0)		{ game->canonLeft(glutGet(GLUT_ELAPSED_TIME));
	}else if(key-'d'==0){ game->canonRight(glutGet(GLUT_ELAPSED_TIME));
	}else if(key-' '==0){ game->fireWeapon();
	}else if(key-'0'<10 && key-'0'>=0){ game->cameraChange(key-'0');
	}else if(key-'l'==0){myIlumination();
	}else if(key-27==0){exit(0);}

		
	







	//glutPostRedisplay();
}




/* My Time:
 * 
 * 
 * 
*/
void myTime(int value){
	game->tick();
	glutTimerFunc(TIMER, myTime, 0);
	glutPostRedisplay();
}





/* My Main:
 * 
 * 
 * 
*/
void main(int argc, char* argv[])
{
	//Inicialização do GameController
	game = new GameController(LEFT_WALL, RIGHT_WALL);
	game->init();

	//Inicialição da Glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	
	//Inicialização da Janela Gráfica
	glutInitWindowSize (720, 720);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Space Invaders 2013"); 

	//Associação das Funções Callbacks
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myInput);
	glutTimerFunc(TIMER, myTime, 1);


	//Z-Buffer e Back-Faces Culling
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	//Enable Iluminação
	glEnable(GL_LIGHTING);
	myIlumination();


	//Inicio do Main Loop da Glut
	glutMainLoop();

}
