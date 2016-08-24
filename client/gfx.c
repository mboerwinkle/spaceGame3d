
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
#include <SDL2/SDL.h>
#include "gfx.h"

#define v3f glVertex3f  /* v3f was the short IRIS GL name for glVertex3f */

void drawShip(point where) {
	GLfloat red = 1.0, green = 0.2, blue = 0.0;

	glPushMatrix();
	glTranslatef((where[0]-50000)/100.0, (where[1]-50000)/100.0, (where[2]-50000)/100.0);
	printf("Translate to (%f, %f, %f)\n", (where[0]-50000)/100.0, (where[1]-50000)/100.0, (where[2]-50000)/100.0);
	/*
	glRotatef(290.0, 1.0, 0.0, 0.0);
	glRotatef(planes[i].angle, 0.0, 0.0, 1.0);
	*/
	glScalef(1.0 / 3.0, 1.0 / 4.0, 1.0 / 4.0); // WTF no, fix this
	glTranslatef(0.0, -4.0, -1.5);
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

void initGfx() {
	//No events etc. for now
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Space Game - 3D edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_OPENGL);
	if (window == NULL) {
		fputs("SDL2 window creation failed", stderr);
		fputs(SDL_GetError(), stderr);
		SDL_Quit();
		return;
	}
	context = SDL_GL_CreateContext(window);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	/* setup OpenGL state */
	glMatrixMode(GL_PROJECTION);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20);
	glMatrixMode(GL_MODELVIEW);
}

void quitGfx() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
