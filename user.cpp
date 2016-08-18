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
	char msg[MSGSIZE] = "SCN";
	unsigned int msgUsed = 3;
	memcpy(msg+msgUsed, &tickCount, sizeof(unsigned int));
	msgUsed+=sizeof(unsigned int);
	for(int x = 0; x<shipList[shipIdx]->myBubble->shipIdx.len; x++){
		memcpy(msg+msgUsed, shipList[shipList[shipIdx]->myBubble->shipIdx.list[x]]->pos, sizeof(point));
		msgUsed+=sizeof(point);
		memcpy(msg+msgUsed, shipList[shipList[shipIdx]->myBubble->shipIdx.list[x]]->rot, sizeof(quat));
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
	if(msgUsed > 3+sizeof(unsigned int)){
		msg[msgUsed] = 0;
		msgUsed++;
		sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
	}
}
