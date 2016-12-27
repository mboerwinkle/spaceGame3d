
//Much of this was plagiarized shamelessly from glutplane.c on the OpenGl examples page. Original copyright notice below.

/* Copyright (c) Mark J. Kilgard, 1994. */

/* This program is freely distributable without licensing fees 
	 and is provided without guarantee or warrantee expressed or 
	 implied. This program is -not- in the public domain. */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "gfx.h"
#include "def.h"
#include "../share/blockUnion.h"
#include "../share/quatOps.h"

#define v3f glVertex3f  /* v3f was the short IRIS GL name for glVertex3f */
void drawCube(signedPoint one, signedPoint two){
	GLfloat red = 0.4, green = 0.5, blue = 0.6;
	float a[3], b[3];
	a[0]= (float)one[0]/100;
	a[1]= (float)one[1]/100;
	a[2]= (float)one[2]/100;
	b[0]= (float)two[0]/100;
	b[1]= (float)two[1]/100;
	b[2]= (float)two[2]/100;
	//FIXME speed
    glBegin(GL_QUADS);
    // front
	glColor3f(red, green, blue);
    glVertex3f(b[0], a[1], a[2]);
    glVertex3f(b[0], b[1], a[2]);
    glVertex3f(b[0], b[1], b[2]);
    glVertex3f(b[0], a[1], b[2]);
    // back
    glVertex3f(a[0], a[1], a[2]);
    glVertex3f(a[0], b[1], a[2]);
    glVertex3f(a[0], b[1], b[2]);
    glVertex3f(a[0], a[1], b[2]);
    // right
	glColor3f(red*0.8, green*0.8, blue*0.8);
    glVertex3f(b[0], b[1], a[2]);
    glVertex3f(a[0], b[1], a[2]);
    glVertex3f(a[0], b[1], b[2]);
    glVertex3f(b[0], b[1], b[2]);
    // left
    glVertex3f(b[0], a[1], a[2]);
    glVertex3f(a[0], a[1], a[2]);
    glVertex3f(a[0], a[1], b[2]);
    glVertex3f(b[0], a[1], b[2]);
    // top
	glColor3f(red*0.6, green*0.6, blue*0.6);
    glVertex3f(a[0], a[1], a[2]);
    glVertex3f(a[0], b[1], a[2]);
    glVertex3f(b[0], b[1], a[2]);
    glVertex3f(b[0], a[1], a[2]);
    // bottom
    glVertex3f(a[0], a[1], b[2]);
    glVertex3f(a[0], b[1], b[2]);
    glVertex3f(b[0], b[1], b[2]);
    glVertex3f(b[0], a[1], b[2]);
    glEnd();	
}
void drawShip(short type, point where, quat rot) {
	glMatrixMode(GL_MODELVIEW);
	GLfloat red = 0.4, green = 0.5, blue = 0.6;
	glPushMatrix();
	double pos[3];
	for (int i = 0; i < 3; i++) {
		if(where[i] > myPos[i]){//FIXME elegance
			pos[i] = (where[i]-myPos[i])/100.0;
		}else{
			pos[i] = (myPos[i]-where[i])/-100.0;
		}
	}
	//FIXME speed. use of glTranslated is slow.
	quat revRot = {rot[0], -rot[1], -rot[2], -rot[3]};
	double rotMatrix[16];
	generateRotationMatrix(revRot, rotMatrix);
	double lookAt[3] = {1,0,0};
	double upVector[3] = {0,0,1};
	rotVector(lookAt, myRot);
	rotVector(upVector, myRot);
	gluLookAt(0,0,0,lookAt[0], lookAt[1], lookAt[2], upVector[0], upVector[1], upVector[2]);
	glTranslated(pos[0], pos[1], pos[2]);
	glMultMatrixd(rotMatrix);
	glRotated(-90, 0, 0, 1);
	glScalef(1.0 / 4.0, 1.0 / 4.0, 1.0 / 3.0); //FIXME WTF no, fix this
	if(shipTypes[type].myBlock == NULL){
		glBegin(GL_TRIANGLE_STRIP);
		/* left wing */
		v3f(-7.0, 0.0, 2.0);
		v3f(-1.0, 0.0, 3.0);
		glColor3f(red, green, blue);
		v3f(-1.0, 7.0, 3.0);
		/* left side */
		glColor3f(0.6 * red, 0.6 * green, 0.6 * blue);
		v3f(0.0, 0.0, 0.0);
		v3f(0.0, 8.0, 0.0);
		/* right side */
		v3f(1.0, 0.0, 3.0);
		v3f(1.0, 7.0, 3.0);
		/* final tip of right wing */
		glColor3f(red, green, blue);
		v3f(7.0, 0.0, 2.0);
		glEnd();
	}else{
		for(int x = 0; x < shipTypes[type].myBlock->blockCount; x++){
			drawCube(shipTypes[type].myBlock->p1[x], shipTypes[type].myBlock->p2[x]);
		}
	}
	glPopMatrix();
}

static SDL_Window *window;
static SDL_GLContext context;

void gfxClear() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void gfxFlip() {
	SDL_GL_SwapWindow(window);
}
int has_joystick = 0;
void initGfx() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	window = SDL_CreateWindow("Space Game - 3D edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		fputs("SDL2 window creation failed", stderr);
		fputs(SDL_GetError(), stderr);
		SDL_Quit();
		return;
	}
	if(SDL_NumJoysticks() > 0){
		SDL_JoystickOpen(0);
		has_joystick = 1;
	}
	context = SDL_GL_CreateContext(window);
	glClearColor(0, 0, 0, 1);
	//Occlusion is a thing
	glEnable(GL_DEPTH_TEST);
	//Edit the projection matrix
	glMatrixMode(GL_PROJECTION);
	//This multiplies a specially designed matrix onto the selected one
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 500);
	//Edit the modelview matrix (The "default" matrix)
	glMatrixMode(GL_MODELVIEW);
	//The default plane model requires each polygon to be a flat color to look right
	glShadeModel(GL_FLAT);//FIXME not anything to fix here. just mentioning that GL_SMOOTH looks hella nice.
}

void quitGfx() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
