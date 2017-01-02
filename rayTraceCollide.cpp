#include "rayTraceCollide.h"
#include "share/quatOps.h"
#include "ship.h"
#include "share/blockUnion.h"
//int64_t shipRayTraceCollide(Ship* targ, point origin, quat dir);
Ship* rayTraceCollide(Bubble* myBub, point origin, quat dir, int64_t* mindist){
	Ship* hit = NULL;
	Ship* targ = NULL;
	int64_t dist;
	*mindist = BUBBLERAD*2+1;//FIXME is this even good?
	for(int impShipIdx = 0; impShipIdx < myBub->closeImportant.len; impShipIdx++){
		targ = shipList[myBub->closeImportant.list[impShipIdx]];
		if(targ == NULL){
			myBub->closeImportant.remove(impShipIdx);
			impShipIdx--;
			continue;
		}
		for(int x = 0; x < targ->myBub->shipIdx.len; x++){
			dist = shipList[targ->myBub->shipIdx.list[x]]->rayCollide(origin, dir);
			if(dist != -1 && dist < *mindist){
				*mindist = dist;
				hit = shipList[targ->myBub->shipIdx.list[x]];
			}
		}
	}
	return hit;
}
/*no longer used. replaced by oop ship function with support for blockunions
int64_t shipRayTraceCollide(Ship* targ, point origin, quat dir){//FIXME OOP. Make this a function of ship.
	point relLoc = {(targ->pos[0]-origin[0]), (targ->pos[1]-origin[1]), (targ->pos[2]-origin[2])};
	quat revRot = {dir[0], -dir[1], -dir[2], -dir[3]};
	rotPoint(relLoc, revRot);
	if(abs(relLoc[1]) < targ->rad && abs(relLoc[2]) < targ->rad && relLoc[0] > 0){
		return relLoc[0];
	}
	return -1;
}*/
