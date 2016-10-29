#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../share/dataTypes.h"
#include "../modules/module.h"
#include "../ship.h"
#include "../user.h"
#include "../def.h"
void netParse(int userIdx, char* msg){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	if(!strcmp(prefix, "CTL")){
		if(userList[userIdx]->shipIdx == -1){
			puts("user tried to send controls without owning a ship.");
			return;
		}
		controls* myControls = &(shipList[userList[userIdx]->shipIdx]->ctl);
		memcpy(myControls, msg+3, sizeof(controls));
	}else if(!strcmp(prefix, "TXT")){
		printf("User%d: %s\n", userIdx, msg+3);
	}else if(!strcmp(prefix, "SPN")){
		puts("Spawning");
		point loc = {500000, 500000, 500000};
		quat rot = {1, 0, 0, 0};
		Ship* newShip = new Ship(0, loc, rot, 1, &(userList[userIdx]->shipIdx));
		new ModLaser(newShip);
	}
	
}
