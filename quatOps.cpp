#include <stdio.h>
#include <stdlib.h>
#include "dataTypes.h"
#include "quatOps.h"
#define W1 append[0]
#define X1 append[1]
#define Y1 append[2]
#define Z1 append[3]
#define W2 targ[0]
#define X2 targ[1]
#define Y2 targ[2]
#define Z2 targ[3]//this is just to allow me to easily copy code from http://www.cprogramming.com/tutorial/3d/quaternions.html
void rotAppend(double* targ, double* append){
	quat newTarg;
	newTarg[0]=(W1 * W2 - X1 * X2 - Y1 * Y2 - Z1 * Z2);
	newTarg[1]=(W1 * X2 + X1 * W2 + Y1 * Z2 - Z1 * Y2);
	newTarg[2]=(W1 * Y2 - X1 * Z2 + Y1 * W2 + Z1 * X2);
	newTarg[3]=(W1 * Z2 + X1 * Y2 - Y1 * X2 + Z1 * W2);
	targ[0]=newTarg[0];
	targ[1]=newTarg[1];
	targ[2]=newTarg[2];
	targ[3]=newTarg[3];
}
