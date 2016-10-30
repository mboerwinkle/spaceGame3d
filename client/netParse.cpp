#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../share/dataTypes.h"
#include "def.h"
#include "gfx.h"

static unsigned int lastFrame = 69;

void netParse(char* msg, int len){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	int64_t cam[3] = {-1000, 0, 600};
	if(!strcmp(prefix, "TXT")){
		printf("%s\n", msg);
	}else if(!strcmp(prefix, "SCN")){
//		printf("%d ships\n", *((unsigned int*)(msg+3+sizeof(unsigned int))));
		unsigned int thing = *(unsigned int*)(msg+3);
#define stepSize (sizeof(short)+sizeof(point)+sizeof(quat))
		int msgUsed = 3+sizeof(unsigned int)*2;
		if(thing != lastFrame){
			lastFrame = thing;
			gfxClear();
			memcpy(myPos, msg+msgUsed+sizeof(short), sizeof(point));
			memcpy(targRot, msg+msgUsed+sizeof(short)+sizeof(point), sizeof(quat));
			rotPoint(cam, myRot);
			for(int temp = 0; temp < 3; temp++){
				myPos[temp] += cam[temp];
			}
			msgUsed+=stepSize;//FIXME should not actually happen
		}
		int shipCount = 0;
		while(msgUsed + (int)stepSize < len){
			short type = *(short*)(msg+msgUsed);
			uint64_t* loc = (uint64_t*)(msg + msgUsed+sizeof(short));
			double* rot = (double*)(msg + msgUsed +sizeof(short)+ sizeof(point));
			drawShip(type, loc, rot);
			msgUsed += stepSize;
			shipCount++;
		}
		//this was the source of the problems. Should only be called if it is the last packet.
		gfxFlip();
	}
}
