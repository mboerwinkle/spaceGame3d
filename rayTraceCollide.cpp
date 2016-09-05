#include "rayTraceCollide.h"
#include "ship.h"
uint64_t shipRayTraceCollide(Ship* targ, point origin, double* uVec);
uint64_t rayTraceCollide(Bubble* myBub, point origin, double* uVec, void* hit){
	Bubble* currBub;
	uint64_t distsq;
	uint64_t mindistsq = BUBBLERAD*4*BUBBLERAD+1;//FIXME is this even good?
	for(int impShipIdx = 0; impShipIdx < myBub->closeImportant.len; impShipIdx++){
		currBub = shipList[myBub->closeImportant.list[impShipIdx]]->myBub;
		for(int x = 0; x < currBub->shipIdx.len; x++){
			distsq = shipRayTraceCollide(shipList[currBub->shipIdx.list[x]], origin, uVec);
			if(distsq != 0 && distsq < mindistsq){
				mindistsq = distsq;
				hit = shipList[currBub->shipIdx.list[x]];
			}
		}
	}
	return mindistsq;
}
uint64_t shipRayTraceCollide(Ship* targ, point origin, double* uVec){
	return 0;
}
