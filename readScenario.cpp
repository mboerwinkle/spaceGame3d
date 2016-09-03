#include <stdio.h>
#include <stdlib.h>
#include "readScenario.h"
#include "dataTypes.h"
#include "ship.h"
#include "ai.h"

void readScenario(char *filename){
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Failed to open scenario \'%s\'\n", filename);
		return;
	}
	int numShips;
	fscanf(fp, "%d", &numShips);
	point loc;
	quat rot;
	int important;
	int speed;
	int index;
	Ship* newShip;
	for(int x = 0; x < numShips; x++){
		fscanf(fp, "%d %ld %ld %ld %lf %lf %lf %lf %d", &important, &(loc[0]), &(loc[1]), &(loc[2]), &(rot[0]), &(rot[1]), &(rot[2]), &(rot[3]), &speed);
		newShip = new Ship(loc, rot, important, &index);
		newShip->myAI = new AI(index);
	}
}
