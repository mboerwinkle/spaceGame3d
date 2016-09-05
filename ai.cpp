#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "def.h"
#include "quatOps.h"
#include "chebDist.h"
#include "ship.h"
#include "user.h"
#include "ai.h"
AI::AI(int shipIdx){
	this->shipIdx = shipIdx;
	important = shipList[shipIdx]->important;
	shipList[shipIdx]->myAI = this;
}
AI::~AI(){
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
		circle(shipList[((shipList[shipIdx]->index+1)%shipCount)]->pos, 1000);
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
	quat revRot = {shipList[shipIdx]->rot[0], -shipList[shipIdx]->rot[1], -shipList[shipIdx]->rot[2], -shipList[shipIdx]->rot[3]};
	rotPoint(relLoc, revRot);
	if(relLoc[2] > 0){
		if(myCtl->pitch+0.1<1){
			if(myCtl->pitch < 0){
				myCtl->pitch += 0.5;//prevents overcorrecting
			}else myCtl->pitch += 0.1;
		}else myCtl->pitch = 1;
	}else{
		if(myCtl->pitch-0.1>-1){
			if(myCtl->pitch > 0){
				myCtl->pitch -= 0.5;//prevents overcorrecting
			}else myCtl->pitch -= 0.1;
		}else myCtl->pitch = -1;
	}
	if((relLoc[1] < 0)){
		if(myCtl->yaw+0.1<1){
			if(myCtl->yaw < 0){
				myCtl->yaw += 0.5;
			}else myCtl->yaw += 0.1;
		}else myCtl->yaw = 1;
	}else{
		if(myCtl->yaw-0.1>-1){
			if(myCtl->yaw > 0){
				myCtl->yaw -= 0.5;
			}else myCtl->yaw -= 0.1;
		}else myCtl->yaw = -1;
	}
	return 0;//FIXME
}
int AI::attack(Ship* targ){
//	signedPoint relLoc = {(int64_t)(loc[0]-(*myLoc)[0]), (int64_t)(loc[1]-(*myLoc)[1]), (int64_t)(loc[2]-(*myLoc)[2])};
//	uint64_t dist = sqrt(relLoc[0]*relLoc[0]+relLoc[1]*relLoc[1]+relLoc[2]*relLoc[2]);
//	if(dist > 
	return 0;
}
void AI::circle(point loc, int rad){
	controls *myCtl = &(shipList[shipIdx]->ctl);
	point* myLoc = &(shipList[shipIdx]->pos);
	signedPoint relLoc = {(int64_t)(loc[0]-(*myLoc)[0]), (int64_t)(loc[1]-(*myLoc)[1]), (int64_t)(loc[2]-(*myLoc)[2])};
	quat revRot = {shipList[shipIdx]->rot[0], -shipList[shipIdx]->rot[1], -shipList[shipIdx]->rot[2], -shipList[shipIdx]->rot[3]};
	rotPoint(relLoc, revRot);
	if(relLoc[0]+rad > 0) relLoc[2]+=rad;
	if(relLoc[2] > 0){
		if(myCtl->pitch+0.1<1){
			if(myCtl->pitch < 0){
				myCtl->pitch += 0.5;//prevents overcorrecting
			}else myCtl->pitch += 0.1;
		}else myCtl->pitch = 1;
	}else{
		if(myCtl->pitch-0.1>-1){
			if(myCtl->pitch > 0){
				myCtl->pitch -= 0.5;//prevents overcorrecting
			}else myCtl->pitch -= 0.1;
		}else myCtl->pitch = -1;
	}
	if((relLoc[1] < 0)){
		if(myCtl->roll+0.1<1){
			if(myCtl->roll < 0){
				myCtl->roll += 0.5;
			}else myCtl->roll += 0.1;
		}else myCtl->roll = 1;
	}else{
		if(myCtl->roll-0.1>-1){
			if(myCtl->roll > 0){
				myCtl->roll -= 0.5;
			}else myCtl->roll -= 0.1;
		}else myCtl->roll = -1;
	}

}
