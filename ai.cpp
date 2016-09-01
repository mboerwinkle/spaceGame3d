#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "def.h"
#include "ship.h"
#include "ai.h"
AI::AI(int shipIdx){
	this->shipIdx = shipIdx;
	important = shipList[shipIdx]->important;
	aiList[aiCount] = this;
	aiCount++;
}
void AI::tick(){
	controls *ctl = &(shipList[shipIdx]->ctl);
	ctl->accel = 0.5;
	ctl->roll = 1;
}
