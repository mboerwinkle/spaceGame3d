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
	if(shipList[shipIdx] == NULL){
		shipIdx = -1;
	}
	if(shipIdx == -1){
		return;
	}
	Ship* myShip = shipList[shipIdx];
	Ship* targ = shipList[shipIdx];
	
	char msg[MSGSIZE] = "SCN";
	unsigned int msgUsed = 3;
	memcpy(msg+msgUsed, &tickCount, sizeof(unsigned int));
	msgUsed+=sizeof(unsigned int);
	for(int impShipIdx = 0; impShipIdx < myShip->myBubble->closeImportant.len; impShipIdx++){
		targ = shipList[myShip->myBubble->closeImportant.list[impShipIdx]];//the ship who has a bubble that we are currently cycling through
		for(int x = 0; x<targ->myBubble->shipIdx.len; x++){
			memcpy(msg+msgUsed, shipList[targ->myBubble->shipIdx.list[x]]->pos, sizeof(point));
			msgUsed+=sizeof(point);
			memcpy(msg+msgUsed, shipList[targ->myBubble->shipIdx.list[x]]->rot, sizeof(quat));
			msgUsed+=sizeof(quat);
			if(sizeof(point)+sizeof(quat) + msgUsed >= MSGSIZE){//FIXME speed
				msg[msgUsed] = 0;
				msgUsed++;
				sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
				char msg[MSGSIZE] = "SCN";
				int msgUsed = 3;
				memcpy(msg+msgUsed, &tickCount, sizeof(unsigned int));
				msgUsed+=sizeof(unsigned int);
			}
		}
	}
	if(msgUsed > 3+sizeof(unsigned int)){
		msg[msgUsed] = 0;
		msgUsed++;
		sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
	}
}
