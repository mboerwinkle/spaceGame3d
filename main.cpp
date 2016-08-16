#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dataTypes.h"
#include "ship.h"
#include "user.h"
#include "def.h"
#include "delay.h"
#include "netListen.h"
using namespace std;
void setupNetwork();
void loop();
void shutdown();

int sockfd;
User* userList[MAXUSERS];
int userCount = 0;
Ship* shipList[MAXSHIPS];
int shipCount = 0;
struct sockaddr_in recvAddr;

int main(){
	setupNetwork();
	loop();
	shutdown();
	return 0;
}
void setupNetwork(){
	recvAddr.sin_family=AF_INET;
	recvAddr.sin_port=htons(6000);
	recvAddr.sin_addr={.s_addr = htonl(INADDR_ANY)};
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr));
	pthread_t networkThread;
	pthread_create(&networkThread, NULL, netListen, NULL);
}
void loop(){
	while(1){
		//send User data
		for(int x = 0; x < userCount; x++){
			userList[x]->sendUserData();
		}
		//tick AIs
		//tickShips (vel/rot changes based on controls, tick modules, advance ships)
		for(int x = 0; x < shipCount; x++){
			shipList[x]->tick();
		}
		//handleCollisions(also, add remove ships from collision boxes)
		
		//wait Until time up.
		delay(60);
	}
}
void shutdown(){
}
