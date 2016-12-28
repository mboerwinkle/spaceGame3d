#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../share/dataTypes.h"
#include "def.h"
#include "gfx.h"

char *data = NULL;
int maxDataLen = 0;
int datalen = 0;
char lastMsgIdx;
char lastPacketIdx;
bool bad = true;
void messageParse();
void netParse(char* msg, int len){
	char thisMsgIdx = msg[0];
	char thisPacketIdx = msg[1];
//	printf("netparse %d %d\n", thisMsgIdx, thisPacketIdx);
	if(thisMsgIdx != lastMsgIdx){//first packet
		lastMsgIdx = thisMsgIdx;
		if(thisPacketIdx != 0){//we missed the first packet :(
			bad = true;
			return;
		}
		if(!bad){//send the completed data to be processed
//			puts("sending message for processing");
			messageParse();
		}
		datalen = 0;
		bad = false;
	}else{//continuation
		if(lastPacketIdx+1 != thisPacketIdx || bad == true){//check for discontinuity
			bad = true;
			return;
		}
	}
	lastPacketIdx = thisPacketIdx;
	if(datalen+len-2 > maxDataLen){
		maxDataLen = datalen+len-2;
		printf("Our biggest message ever! Reallocating! %d\n", maxDataLen);
		data = (char*)realloc(data, maxDataLen);
	}
	memcpy(data+datalen, msg+2, len-2);
	datalen+=len-2;
}
void messageParse(){
//	fwrite(data, 1, datalen, stdout);
//	printf("\ndatalen %d\n", datalen);
	char prefix[4] = {data[0], data[1], data[2], 0};
	int64_t cam[3] = {-1000, 0, 600};
	if(!strcmp(prefix, "TXT")){
		printf("%s\n", data+3);
	}else if(!strcmp(prefix, "SCN")){
		#define shipSize (sizeof(short)+sizeof(point)+sizeof(quat))
		int dataUsed = 3;
		short shipsUsed = *((short*)(data+dataUsed)); dataUsed+=sizeof(short);
		short povShipIdx = *((short*)(data+dataUsed)); dataUsed+=sizeof(short);
//		printf("shipsUsed: %hd\npovIdx: %hd\n", shipsUsed, povShipIdx);
		gfxClear();
		memcpy(myPos, data+dataUsed+shipSize*povShipIdx+sizeof(short), sizeof(point));
//		printf("mypos %d %d %d\n", myPos[0], myPos[1], myPos[2]);
		memcpy(targRot, data+dataUsed+shipSize*povShipIdx+sizeof(short)+sizeof(point), sizeof(quat));
		rotPoint(cam, myRot);
		for(int temp = 0; temp < 3; temp++){
			myPos[temp] += cam[temp];
		}
		for(int shipCount = 0; shipCount < shipsUsed; shipCount++){
			short type = *(short*)(data+dataUsed+shipCount*shipSize);
			int64_t* loc = (int64_t*)(data+dataUsed+shipCount*shipSize+sizeof(short));
			double* rot = (double*)(data+dataUsed+shipCount*shipSize+sizeof(short)+ sizeof(point));
			drawShip(type, loc, rot);
		}
		dataUsed+=shipsUsed*shipSize;
		short gfxCount = *((short*)(data+dataUsed)); dataUsed+=sizeof(short);
		drawable thisDrawable;
		for(int temp = 0; temp < gfxCount; temp++){
			memcpy(&thisDrawable, data+dataUsed+temp*sizeof(drawable), sizeof(drawable));
			drawDrawable(thisDrawable);
		}
		gfxFlip();
	}
}
