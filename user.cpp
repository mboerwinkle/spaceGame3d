#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "ship.h"
#include "user.h"
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
	Ship* myShip = shipList[shipIdx];
	Ship* targ = shipList[shipIdx];
	
	char msg[MSGSIZE] = "SCN";
	memcpy(msg+3, &tickCount, sizeof(unsigned int));
	unsigned int* shipsUsed = (unsigned int*)(msg+3+sizeof(unsigned int));
	*shipsUsed = 0;
	unsigned int msgUsed = 3+sizeof(unsigned int)*2;
	memcpy(msg+msgUsed, &(myShip->shipType), sizeof(short));
	msgUsed+=sizeof(short);
	memcpy(msg+msgUsed, myShip->pos, sizeof(point));//make sure your ship is first so that you get the proper pov
	msgUsed+=sizeof(point);
	memcpy(msg+msgUsed, myShip->rot, sizeof(quat));
	msgUsed+=sizeof(quat);
	(*shipsUsed)++;
	for(int impShipIdx = 0; impShipIdx < myShip->myBub->closeImportant.len; impShipIdx++){
		targ = shipList[myShip->myBub->closeImportant.list[impShipIdx]];//the ship who has a bubble that we are currently cycling through
		if(targ == NULL){
			myShip->myBub->closeImportant.remove(impShipIdx);
			impShipIdx--;
			continue;
		}
		for(int x = 0; x<targ->myBub->shipIdx.len; x++){
			Ship* currShip = shipList[targ->myBub->shipIdx.list[x]];
			memcpy(msg+msgUsed, &(currShip->shipType), sizeof(short));
			msgUsed+=sizeof(short);
			memcpy(msg+msgUsed, currShip->pos, sizeof(point));
			msgUsed+=sizeof(point);
			memcpy(msg+msgUsed, currShip->rot, sizeof(quat));
			msgUsed+=sizeof(quat);
			(*shipsUsed)++;
			if(sizeof(short)+sizeof(point)+sizeof(quat) + msgUsed >= MSGSIZE){//FIXME speed
				sendto(sockfd, msg, msgUsed+1, 0, (struct sockaddr*)&(this->addr), sizeof(this->addr));
				(*shipsUsed) = 0;
				msgUsed = 3+sizeof(unsigned int)*2;
			}
		}
	}
	if(msgUsed > 3+sizeof(unsigned int)*2){
		sendto(sockfd, msg, msgUsed+1, 0, (struct sockaddr*)&(addr), sizeof(addr));
	}
}
