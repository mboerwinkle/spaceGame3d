#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "def.h"
#include "user.h"
#include "ship.h"
#include "netListen.h"
#include "netParse.h"
void* netListen(void *null){
	char msg[MSGSIZE];
	struct sockaddr_in incomingAddr;
	incomingAddr.sin_family=AF_INET;
	incomingAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	incomingAddr.sin_port = htons(6000);
	bind(sockfd, (struct sockaddr*)&incomingAddr, sizeof(incomingAddr));
	socklen_t len;
	while(1){
		int found = 0;
		len = sizeof(incomingAddr);
		recvfrom(sockfd, msg, MSGSIZE, 0, (struct sockaddr*)&incomingAddr, &len);
		for(int x = 0; x < userCount; x++){
			if(userList[x]->addr.sin_addr.s_addr == incomingAddr.sin_addr.s_addr){
				found = 1;
				netParse(x, msg);
			}
		}
		if(!found){
			if(strcmp("joining", msg)) continue;
			userList[userCount] = new User(incomingAddr.sin_addr.s_addr);
			userCount++;
		}
	}
}
