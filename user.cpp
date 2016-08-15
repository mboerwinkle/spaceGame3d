#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
#include "user.h"

User::User(unsigned long ip){
	addr.sin_family=AF_INET;
	addr.sin_port=htons(5999);
	addr.sin_addr.s_addr=ip;
}
void User::sendUserData(){
//	if(view == NULL){
//		return;
//	}
	int msgUsed = 0;
	char msg[MSGSIZE];
	memset(msg, 0, sizeof(msg));
	//later replace with meaningful code
	strcpy(msg, "TEXT:sup fam?");
	msgUsed+=13;
	sendto(sockfd, msg, msgUsed, 0, (struct sockaddr*)&(addr), sizeof(addr));
}
