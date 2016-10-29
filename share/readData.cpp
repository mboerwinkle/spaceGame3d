#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "blockUnion.h"
shipProto *shipTypes;
int shipTypeCount;
void readData(){
	FILE* fp = fopen("ships.cfg", "r");
	if(fp == NULL){
		puts("failed to open ships.cfg");
	}
	fscanf(fp, "%d", &shipTypeCount);
	shipTypes = (shipProto*)calloc(shipTypeCount, sizeof(shipProto));
	char blockUnionFile[80];
	for(int x = 0; x < shipTypeCount; x++){
		fscanf(fp, "%d %d %d %d %lf %lf %lf %s", &(shipTypes[x].maxSpeed),  &(shipTypes[x].accel),  &(shipTypes[x].decel), &(shipTypes[x].rad), &(shipTypes[x].rollAngle),  &(shipTypes[x].yawAngle),  &(shipTypes[x].pitchAngle),  blockUnionFile);
		if(strcmp("NONE", blockUnionFile)){
			shipTypes[x].myBlock = new BlockUnion(blockUnionFile);
		}else{
			shipTypes[x].myBlock = nullptr;
		}
	}
	for(int temp = 0; temp < shipTypeCount; temp++){
		printf("ship %d:\n\tmaxSpeed %d\n\taccel %d\n\tdecel %d\n\trad: %d\n\tangles: %lf %lf %lf\n\tBlockUnion: %p\n", temp, shipTypes[temp].maxSpeed, shipTypes[temp].accel, shipTypes[temp].decel, shipTypes[temp].rad, shipTypes[temp].rollAngle, shipTypes[temp].yawAngle, shipTypes[temp].pitchAngle, shipTypes[temp].myBlock);
	}

}
