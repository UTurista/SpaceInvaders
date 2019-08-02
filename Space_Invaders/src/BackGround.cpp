
#include "BackGround.h"
#include "Material.h"
#include "glbmp.h"
#include <iostream>
#include <string>

using std::cerr;
using std::endl;
using std::string;

GLuint texname;

BackGround::BackGround() {}

void BackGround::LoadTexture(const char* bitmap_file)
{

    glbmp_t bitmap; //object to fill with data from glbmp

    //try to load the specified file--if it fails, dip out
    if (!glbmp_LoadBitmap(bitmap_file, 0, &bitmap)) {
        cerr << "Error loading bitmap file: " << bitmap_file << endl;
        exit(1);
    }

    glGenTextures(1, &texname);
    glBindTexture(GL_TEXTURE_2D, texname);
    //copy data from bitmap into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.width, bitmap.height,
        0, GL_RGB, GL_UNSIGNED_BYTE, bitmap.rgb_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); /* não era necessário pois este comando é executado por omiss‹o */
    //free the bitmap
    glbmp_FreeBitmap(&bitmap);
}

void BackGround::draw()
{

    int x, y;

    glEnable(GL_TEXTURE_2D);

    LoadTexture("SpaceInv.bmp");

    Material mat;
    mat.predefMaterial(BACKGROUND);

    glPushMatrix();
    glBegin(GL_QUADS);

    /*for(y=0; y<100; y++)
		for(x=-50; x<50; x++){

			glBegin(GL_QUADS);

			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 0);
			glVertex3f(x, y , -6);
			glTexCoord2f(0, 1);
			glVertex3f(x+1, y , -6);
			glTexCoord2f(1, 1);
			glVertex3f(x+1, y+1 , -6);
			glTexCoord2f(1, 0);
			glVertex3f(-x, y+1 , -6);

			glEnd();
			}}*/

    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-100, 0, -6);
    glTexCoord2f(0, 10);
    glVertex3f(100, 0, -6);
    glTexCoord2f(10, 10);
    glVertex3f(100, 200, -6);
    glTexCoord2f(10, 0);
    glVertex3f(-100, 200, -6);

    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}