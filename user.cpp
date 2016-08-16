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
	Ship* targ = shipList[shipIdx];
	char msg[MSGSIZE] = "SCN";
	int msgUsed = 3;
	memcpy(msg+3, targ->pos, sizeof(point));
	memcpy(msg+3+sizeof(point), targ->rot, sizeof(quat));
	msgUsed+=sizeof(point)+sizeof(quat);
	sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
	
}
