#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "def.h"
#include "gfx.h"

static unsigned int lastFrame = 69;

void netParse(char* msg, int len){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	if(!strcmp(prefix, "TXT")){
		printf("%s\n", msg);
	}else if(!strcmp(prefix, "SCN")){
//		printf("%d ships\n", *((unsigned int*)(msg+3+sizeof(unsigned int))));
		unsigned int thing = *(unsigned int*)(msg+3);
#define stepSize (sizeof(point)+sizeof(quat))
		int msgUsed = 3+sizeof(unsigned int)*2;
		if(thing != lastFrame){
			lastFrame = thing;
			gfxClear();
			memcpy(myPos, msg+msgUsed, sizeof(point));
			memcpy(myRot, msg+msgUsed+sizeof(point), sizeof(quat));
			msgUsed+=stepSize;//FIXME should not actually happen
		}
		int shipCount = 0;
		while(msgUsed + (int)stepSize < len){
			uint64_t* loc = (uint64_t*)(msg + msgUsed);
			double* rot = (double*)(msg + msgUsed + sizeof(point));
			drawShip(loc, rot);
			msgUsed += stepSize;
			shipCount++;
		}
		//this was the source of the problems. Should only be called if it is the last packet.
		gfxFlip();
	}
}
