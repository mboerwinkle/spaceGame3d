#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "ship.h"
#include "user.h"
#include "sendMessage.h"
User::User(unsigned long ip){
	addr.sin_family=AF_INET;
	addr.sin_port=htons(5999);
	addr.sin_addr.s_addr=ip;
	userList[userCount] = this;
	userCount++;
}
void User::sendUserData(){
	if(shipList[shipIdx] == NULL){
		shipIdx = -1;
	}
	if(shipIdx == -1){
		return;
	}

	static char data[100000];//FIXME check for overflow.
	int datalen = 0;
	strcpy(data, "SCN"); datalen+=3;
	short* shipsUsed = (short*)(data+datalen); datalen+=sizeof(short);
	(*shipsUsed) = 0;
	short* povShipIdx = (short*)(data+datalen); datalen+=sizeof(short);
	Ship* myShip = shipList[shipIdx];
	Ship* targ = shipList[shipIdx];

	for(int impShipIdx = 0; impShipIdx < myShip->myBub->closeImportant.len; impShipIdx++){
		targ = shipList[myShip->myBub->closeImportant.list[impShipIdx]];//the ship who has a bubble that we are currently cycling through
		if(targ == NULL){
			myShip->myBub->closeImportant.remove(impShipIdx);
			impShipIdx--;
			continue;
		}
		for(int x = 0; x<targ->myBub->shipIdx.len; x++){
			Ship* currShip = shipList[targ->myBub->shipIdx.list[x]];
			if(currShip == myShip){
				(*povShipIdx) = (*shipsUsed);
			}
			memcpy(data+datalen, &(currShip->shipType), sizeof(short));
			datalen+=sizeof(short);
			memcpy(data+datalen, currShip->pos, sizeof(point));
			datalen+=sizeof(point);
			memcpy(data+datalen, currShip->rot, sizeof(quat));
			datalen+=sizeof(quat);
			(*shipsUsed)++;
		}
	}
	strcpy(data+datalen, "END"); datalen+=3;
	sendMessage(&addr, data, datalen);
}
