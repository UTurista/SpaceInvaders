#ifndef _GLUT_H_
#define _GLUT_H_
#include <GL/glut.h>
#endif

#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_
#include <iostream>
#endif

int ilumination(0);


void myDisplay(void);

int min(int a, int b){return (a>b) ? b: a;}

void myCamera();

void myReshape(GLsizei w, GLsizei h);

void myInput(unsigned char key, int x, int y);

void myTime(int value);

void main(int argc, char* argv[]);

void myIlumination();
