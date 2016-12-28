#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../def.h"
#include "../ship.h"
#include "modLaser.h"
#include "../rayTraceCollide.h"
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
	Ship* hit;
	uint64_t dist;
	Bubble* disBub;
	if(owner->important){
		disBub = owner->myBub;
	}else disBub = shipList[owner->myImp]->myBub;
	drawable* disDrawable = &(disBub->drawables[disBub->drawableCount]);
	disBub->drawableCount++;
	disDrawable->type = 0;
	{//FIXME two things wrong here. Shouldn't have to calculate direction vector and shouldnt have to run three lines to copy a vector.
	disDrawable->pos[0] = owner->pos[0];
	disDrawable->pos[1] = owner->pos[1];
	disDrawable->pos[2] = owner->pos[2];
	double shipDir[3] = {1, 0, 0};
	memcpy(&(disDrawable->dir), shipDir, sizeof(vec));
	rotVector(disDrawable->dir, owner->rot);
	}
	hit = rayTraceCollide(disBub, owner->pos, owner->rot, &dist);
	if(hit != NULL){
		printf("HIT %p %ld\n", hit, dist);
		delete hit;
	}
}
