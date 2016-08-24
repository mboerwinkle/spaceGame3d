#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "gfx.h"

static unsigned int lastFrame = 69;

void netParse(char* msg, int len){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	if(!strcmp(prefix, "CTL")){
		//overwrite control 
	}else if(!strcmp(prefix, "TXT")){
		printf("%s\n", msg);
	}else if(!strcmp(prefix, "SCN")){
		puts("Got scan!");
		unsigned int thing = *(unsigned int*)(msg+3);
		if(thing != lastFrame){
			lastFrame = thing;
			gfxClear();
		}
		int msgUsed = 3+sizeof(thing);
#define stepSize (sizeof(point)+sizeof(quat))
		while(msgUsed + (int)stepSize < len){
			drawShip((uint64_t*)(msg + msgUsed));
			msgUsed += stepSize;
		}
		gfxFlip();
	}
}
