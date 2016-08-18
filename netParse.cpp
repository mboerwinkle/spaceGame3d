#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataTypes.h"
#include "ship.h"
#include "user.h"
#include "def.h"
void netParse(int userIdx, char* msg){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	if(!strcmp(prefix, "CTL")){
		//overwrite control 
	}else if(!strcmp(prefix, "TXT")){
		//text
	}else if(!strcmp(prefix, "SPN")){
		puts("Spawning");
		point loc = {500000, 500000, 500000};
		quat rot = {1, 0, 0, 0};
		new Ship(loc, rot, 1, &(userList[userIdx]->shipIdx));
	}
	
}
