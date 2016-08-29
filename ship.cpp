#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"
#include "ship.h"
#include "bubble.h"
#include "chebDist.h"
#include "quatOps.h"

Ship::Ship(point pos, quat rot, int important, int* idx){
	puts("loading ships");
	memcpy(this->pos, pos, sizeof(point));
	memcpy(this->rot, rot, sizeof(quat));
	this->important = important;
	shipList[shipCount] = this;
	index = shipCount;
	if(important){
		importants.add(index);
		myBubble = new Bubble(this);
		tickImportant();//this prevents an important ship from accidentally being added to a different ship's bubble instead of its own
	}else{
		orphans.add(index);
	}
	if(idx != NULL) *idx = index;
	shipCount++;
}
void Ship::tick(){
	applyControls();
	addSpeed();
}
void Ship::tickImportant(){//remember, this needs to be able to handle some frames where a bubble is in one bubble's closeImportant list but not reciprocated
	if(!important){
		puts("error blagrug");
	}
	myBubble->updateOrphans();
	for(int x = 0; x < importants.len; x++){
		if(chebDist(shipList[importants.list[x]], this) < 2*BUBBLERAD && -1 == myBubble->closeImportant.search(importants.list[x])){
			myBubble->closeImportant.add(importants.list[x]);
		}
	}
	for(int x = 0; x < myBubble->closeImportant.len; x++){
		if(chebDist(shipList[myBubble->closeImportant.list[x]], this) > 2*BUBBLERAD){
			myBubble->closeImportant.remove(x);
			
		}
	}
}
void Ship::applyControls(){
	//ctl.accel
	if(speed+accel < maxSpeed*ctl.accel){
		speed+=accel;
	}else if(speed-decel > maxSpeed*ctl.accel){
		speed-=decel;
	}
	else{
		speed = maxSpeed*ctl.accel;
	}
	//math.stackexchange.com/questions/40164/how-do-you-rotate-a-vector-by-a-unit-quaternion#40169
	if(ctl.yaw != 0){
		double angleChg = ctl.yaw*yawAngle;
		quat addRot = {cos(0.5*angleChg), 0, 0, sin(0.5*angleChg)};
		rotAppend(rot, addRot, rot);
	}
	if(ctl.roll != 0){
		double angleChg = ctl.roll*rollAngle;
		quat addRot = {cos(0.5*angleChg), sin(0.5*angleChg), 0, 0};
		rotAppend(rot, addRot, rot);
	}
	if(ctl.pitch != 0){
		double angleChg = ctl.pitch*pitchAngle;
		quat addRot = {cos(0.5*angleChg), 0, sin(0.5*angleChg), 0};
		rotAppend(rot, addRot, rot);
	}
}
void Ship::addSpeed(){
	double axis[3] = {1, 0, 0};
	rotVector(axis, rot);
	pos[0]+=speed*axis[0];
	pos[1]+=speed*axis[1];
	pos[2]+=speed*axis[2];
	//sorry fam, looks like your kode is broken
//	pos[0]+=speed*(rot[0]*rot[0]+rot[1]*rot[1]-rot[2]*rot[2]-rot[3]*rot[3]);
//	pos[1]+=speed*(2*rot[0]*rot[3]+2*rot[1]*rot[2]);
//	pos[2]+=speed*(-2*rot[0]*rot[2]+2*rot[1]*rot[3]);
}

