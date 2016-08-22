#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "ship.h"
#include "bubble.h"
#include "chebDist.h"

Ship::Ship(point pos, quat rot, int important, int* idx){
	memcpy(this->pos, pos, sizeof(point));
	memcpy(this->rot, rot, sizeof(quat));
	this->important = important;
	shipList[shipCount] = this;
	index = shipCount;
	if(important){
		importants.add(index);
		myBubble = new Bubble(this);
	}else{
		orphans.add(index);
	}
	*idx = index;
	shipCount++;
}
void Ship::tick(){
	addSpeed();
	applyControls();
}
void Ship::tickImportant(){
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
	//ctl.yaw
	
	//ctl.roll
	//ctl.pitch
}
void Ship::addSpeed(){
	pos[0]+=speed*(rot[0]*rot[0]+rot[1]*rot[1]-rot[2]*rot[2]-rot[3]*rot[3]);
	pos[1]+=speed*(2*rot[0]*rot[3]+2*rot[1]*rot[2]);
	pos[2]+=speed*(-2*rot[0]*rot[2]+2*rot[1]*rot[3]);
}

