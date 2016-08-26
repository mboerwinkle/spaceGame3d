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
}
void User::sendUserData(){
	if(shipIdx == -1){
		return;
	}
	if(shipList[shipIdx] == NULL){
		shipIdx = -1;
	}
	Ship* myShip = shipList[shipIdx];
	Ship* targ = shipList[shipIdx];
	
	char msg[MSGSIZE] = "SCN";
	memcpy(msg+3, &tickCount, sizeof(unsigned int));
	unsigned int* shipsUsed = (unsigned int*)(msg+3+sizeof(unsigned int));
	unsigned int msgUsed = 3+sizeof(unsigned int)*2;
	for(int impShipIdx = 0; impShipIdx < myShip->myBubble->closeImportant.len; impShipIdx++){
		targ = shipList[myShip->myBubble->closeImportant.list[impShipIdx]];//the ship who has a bubble that we are currently cycling through
		for(int x = 0; x<targ->myBubble->shipIdx.len; x++){
			memcpy(msg+msgUsed, shipList[targ->myBubble->shipIdx.list[x]]->pos, sizeof(point));
			msgUsed+=sizeof(point);
			memcpy(msg+msgUsed, shipList[targ->myBubble->shipIdx.list[x]]->rot, sizeof(quat));
			msgUsed+=sizeof(quat);
			(*shipsUsed)++;
			if(sizeof(point)+sizeof(quat) + msgUsed >= MSGSIZE){//FIXME speed
				sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
				(*shipsUsed) = 0;
				msgUsed = 3+sizeof(unsigned int)*2;
			}
		}
	}
	if(msgUsed > 3+sizeof(unsigned int)*2){
		sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
	}
}
