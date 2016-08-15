#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "ship.h"


Ship::Ship(point pos, quat rot, int important){
	memcpy(this->pos, pos, sizeof(point));
	memcpy(this->rot, rot, sizeof(quat));
	this->important = important;
}
void Ship::tick(){
	addSpeed();
}
void Ship::addSpeed(){
	pos[0]+=speed*(rot[0]*rot[0]+rot[1]*rot[1]-rot[2]*rot[2]-rot[3]*rot[3]);
	pos[1]+=speed*(2*rot[0]*rot[3]+2*rot[1]*rot[2]);
	pos[2]+=speed*(-2*rot[0]*rot[2]+2*rot[1]*rot[3]);
}

