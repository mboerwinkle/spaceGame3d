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
	int radius;
	signedPoint *p1;//every dimension of p1 should be smaller than p2
	signedPoint *p2;
	void calculateRadius();
	int sphereCollide(signedPoint pos, quat rot, int rad);
	int64_t rayCollide(point orig, quat dir);
};
#endif
