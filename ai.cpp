#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "def.h"
#include "quatOps.h"
#include "chebDist.h"
#include "ship.h"
#include "ai.h"
AI::AI(int shipIdx){
	this->shipIdx = shipIdx;
	important = shipList[shipIdx]->important;
	aiList[aiCount] = this;
	aiCount++;
}
void AI::tick(){
	//bubbles assign objectives
	//this section is about fulfilling objectives. All ships need to do this.
	//FIXME set precision that location objectives need to be fulfilled to.
	//FIXME set objective numbers in defines.
	if(objective == -1){//no objective. Maybe return to home?
		return;
	}else if(objective == 0){//go to objLoc then set objective to -1.
		if(go(objLoc)){//FIXME have go return distance from objective?
			objective = -1;
		}
	}else if(objective == 1){//go to objLoc, but do not set objective to -1 on arrival. try to stay in place instead.
		go(objLoc);
	}else if(objective == 2){//attack shipList[objIdx]
		if(chebDist(shipList[shipIdx], shipList[objIdx]) > BUBBLERAD){
			objective = -1;
		}
		if(attack(shipList[objIdx])){
			objective = -1;
		}
	}else if(objective == 3){//try to catch up with shipList[objIdx]
		go(shipList[objIdx]->pos);
	}
}
int AI::go(point loc){
	controls *myCtl = &(shipList[shipIdx]->ctl);
	point* myLoc = &(shipList[shipIdx]->pos);
	signedPoint relLoc = {(int64_t)(loc[0]-(*myLoc)[0]), (int64_t)(loc[1]-(*myLoc)[1]), (int64_t)(loc[2]-(*myLoc)[2])};
	rotPoint(relLoc, shipList[shipIdx]->rot);
	printf("%ld %ld %ld\n", relLoc[0], relLoc[1], relLoc[2]);
	if(relLoc[2] < 0){
		myCtl->pitch = 1;
	}else{
		myCtl->pitch = -1;
	}
	if((relLoc[1] > 0)){
		myCtl->yaw = 1;
	}else{
		myCtl->yaw = -1;
	}
//	if(relLoc[0] < 0){
//		myCtl->yaw*=-1;
//		myCtl->pitch*=-1;
//	}
	return 0;//FIXME
}
int AI::attack(Ship* targ){
	return 0;
}
void AI::circle(point loc, int rad){

}
