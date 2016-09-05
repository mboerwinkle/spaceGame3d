#include <stdlib.h>
#include <stdio.h>
#include "../def.h"
#include "../ship.h"
#include "modLaser.h"
ModLaser::ModLaser(Ship* owner){
	this->owner = owner;
	int good = 0;
	for(int x = 0; x < MAXMODULES; x++){
		if(owner->myMod[x] == NULL){
			owner->myMod[x] = this;
			good = 1;
			break;
		}
	}
	if(good == 0) puts("Fatal module error");
}
ModLaser::~ModLaser(){
}
void ModLaser::tick(int stat){
	if(coolDown > 0) coolDown--;
	if(stat && coolDown <= 0){
		coolDown = maxCoolDown;
		fire();
	}
}
void ModLaser::fire(){
}
