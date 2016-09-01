#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void rotAppend(double* targ, double* append, double* save){
	quat newTarg;
	newTarg[0]=(W1 * W2 - X1 * X2 - Y1 * Y2 - Z1 * Z2);
	newTarg[1]=(W1 * X2 + X1 * W2 + Y1 * Z2 - Z1 * Y2);
	newTarg[2]=(W1 * Y2 - X1 * Z2 + Y1 * W2 + Z1 * X2);
	newTarg[3]=(W1 * Z2 + X1 * Y2 - Y1 * X2 + Z1 * W2);
	quatNormalize(newTarg);//FIXME efficency does not need to fix every tick
	memcpy(save, newTarg, sizeof(quat));
/*	save[0]=newTarg[0];
	save[1]=newTarg[1];
	save[2]=newTarg[2];
	save[3]=newTarg[3];
*/
}
double quatLen(quat r){
	return sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]+r[3]*r[3]);
}
void quatNormalize(quat r){
	double val = quatLen(r);
	r[0]/=val;
	r[1]/=val;
	r[2]/=val;
	r[3]/=val;
}
void rotVector(double* uVec, quat rot){
	quat pureVec = {0, uVec[0], uVec[1], uVec[2]};
	quat revRot = {rot[0], -rot[1], -rot[2], -rot[3]};
	rotAppend(rot, pureVec, pureVec);
	rotAppend(pureVec, revRot, pureVec);
	uVec[0] = pureVec[1];
	uVec[1] = pureVec[2];
	uVec[2] = pureVec[3];
}
/*
M[0]  M[4]  M[8]  M[12]
M[1]  M[5]  M[9]  M[13]
M[2]  M[6]  M[10] M[14]
M[3]  M[7]  M[11] M[15]
*/
void generateRotationMatrix(quat rot, double *M){
	M[0] = 1-2*rot[2]*rot[2]-2*rot[3]*rot[3];
	M[1] = 2*rot[1]*rot[2]+2*rot[0]*rot[3];
	M[2] = 2*rot[1]*rot[3]-2*rot[0]*rot[2];
	M[3] = 0;
	M[4] = 2*rot[1]*rot[2]-2*rot[0]*rot[3];
	M[5] = 1-2*rot[1]*rot[1]-2*rot[3]*rot[3];
	M[6] = 2*rot[2]*rot[3]+2*rot[0]*rot[1];
	M[7] = 0;
	M[8] = 2*rot[1]*rot[3]+2*rot[0]*rot[2];
	M[9] = 2*rot[2]*rot[3]-2*rot[0]*rot[1];
	M[10] = 1-2*rot[1]*rot[1]-2*rot[2]*rot[2];
	M[11] = 0;
	M[12] = 0;
	M[13] = 0;
	M[14] = 0;
	M[15] = 1;
}
