#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
//	double val = sqrt(newTarg[0]*newTarg[0]+newTarg[1]*newTarg[1]+newTarg[2]*newTarg[2]+newTarg[3]*newTarg[3]);
	targ[0]=newTarg[0];//val;
	targ[1]=newTarg[1];//val;
	targ[2]=newTarg[2];//val;
	targ[3]=newTarg[3];//val;
}
void rotVector(quat unitVector, quat rot){
	quat rotCpy = {rot[0], rot[1], rot[2], rot[3]};
	quat revRotCpy = {rot[0], -rot[1], -rot[2], -rot[3]};
	rotAppend(rotCpy, unitVector);
	rotAppend(rotCpy, revRotCpy);
	unitVector[0] = 0;
	unitVector[1] = rotCpy[1];
	unitVector[2] = rotCpy[2];
	unitVector[3] = rotCpy[3];
}
