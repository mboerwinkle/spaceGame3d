#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dataTypes.h"
#include "blockUnion.h"
#include "quatOps.h"
BlockUnion::BlockUnion(char* name){
	FILE* fp = fopen(name, "r");
	if(fp == NULL){
		printf("error opening BlockUnion: %s\n", name);
		return;
	}
	fscanf(fp, "%d", &blockCount);
	p1 = (signedPoint*)calloc(blockCount, sizeof(signedPoint));
	p2 = (signedPoint*)calloc(blockCount, sizeof(signedPoint));
	for(int x = 0; x<blockCount; x++){
		fscanf(fp, "%ld %ld %ld %ld %ld %ld", &(p1[x][0]), &(p1[x][1]), &(p1[x][2]), &(p2[x][0]), &(p2[x][1]), &(p2[x][2]));
	}
}
BlockUnion::~BlockUnion(){
	puts("Are you SURE you want to free a BlockUnion?");
	free(p1);
	free(p2);
}
int BlockUnion::sphereCollide(signedPoint pos, quat rot, int rad){
	quat revRot = {rot[0], -rot[1], -rot[2], -rot[3]};
	rotPoint(pos, revRot);
	signedPoint *a, *b;
	for(int x = 0; x< blockCount; x++){
		a = &(p1[x]);
		b = &(p2[x]);
		if(pos[0]+rad > (*a)[0] && pos[1]+rad > (*a)[1] && pos[2]+rad > (*a)[2] && pos[0]-rad < (*b)[0] && pos[1]-rad < (*b)[1] && pos[2]-rad < (*b)[2]){
			return 1;
		}
	}
	return 0;
}

