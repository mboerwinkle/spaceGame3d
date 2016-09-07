#include "rayTraceCollide.h"
#include "quatOps.h"
#include "ship.h"
int64_t shipRayTraceCollide(Ship* targ, point origin, quat dir);
Ship* rayTraceCollide(Bubble* myBub, point origin, quat dir, uint64_t* mindist){
	Ship* hit = NULL;
	Bubble* currBub;
	uint64_t dist;
	*mindist = BUBBLERAD*2+1;//FIXME is this even good?
	for(int impShipIdx = 0; impShipIdx < myBub->closeImportant.len; impShipIdx++){
		currBub = shipList[myBub->closeImportant.list[impShipIdx]]->myBub;
		for(int x = 0; x < currBub->shipIdx.len; x++){
			dist = shipRayTraceCollide(shipList[currBub->shipIdx.list[x]], origin, dir);
			if(dist != 0 && dist < *mindist){
				*mindist = dist;
				hit = shipList[currBub->shipIdx.list[x]];
			}
		}
	}
	return hit;
}
int64_t shipRayTraceCollide(Ship* targ, point origin, quat dir){
	signedPoint relLoc = {(int64_t)(targ->pos[0]-origin[0]),(int64_t)(targ->pos[1]-origin[1]),(int64_t)(targ->pos[2]-origin[2])};
	quat revRot = {dir[0], -dir[1], -dir[2], -dir[3]};
	rotPoint(relLoc, revRot);
	if(abs(relLoc[1]) < targ->rad && abs(relLoc[2]) < targ->rad && relLoc[0] > 0){
		return relLoc[0];
	}
	return 0;
}
