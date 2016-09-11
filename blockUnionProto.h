#ifndef BLOCKUNIONPROTO_H
#define BLOCKUNIONPROTO_H
#include <math.h>
#include "dataTypes.h"
#include "def.h"
class BlockUnionProto{
public:
	BlockUnionProto(char* name);
	~BlockUnionProto();
	int blockCount;
	signedPoint *p1;//every dimension of p1 should be smaller than p2
	signedPoint *p2;
	int sphereCollide(signedPoint pos, quat rot, int rad);
};
#endif
