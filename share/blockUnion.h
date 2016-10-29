#ifndef BLOCKUNION_H
#define BLOCKUNION_H
#include <math.h>
#include "dataTypes.h"
#include "quatOps.h"
#include "../def.h"
class BlockUnion{
public:
	BlockUnion(char* name);
	~BlockUnion();
	int blockCount;
	signedPoint *p1;//every dimension of p1 should be smaller than p2
	signedPoint *p2;
	int sphereCollide(signedPoint pos, quat rot, int rad);
};
#endif
