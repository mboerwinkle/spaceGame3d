#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "share/dataTypes.h"
#include "ship.h"
#include "user.h"
#include "ai.h"
#include "def.h"
#include "delay.h"
#include "net/listen.h"
#include "scenarios/readScenario.h"
#include "share/blockUnion.h"
#include "share/readData.h"
using namespace std;
void setupNetwork();
void loop();
void shutdown();
void readData();

int sockfd;
User* userList[MAXUSERS];
int userCount = 0;
Ship* shipList[MAXSHIPS];
int shipCount = 0;
IntList orphans;
IntList importants;
struct sockaddr_in recvAddr;
unsigned int tickCount = 0;

int main(int argc, char** argv){
	readData();
	if(argc > 1){
		readScenario(argv[1]);//maybe later have a generate scenario function?
	}
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
	int count = 0;
	while(1){
		//send User data
		for(int x = 0; x < userCount; x++){
			userList[x]->sendUserData();
		}

		//handleCollisions(also, add remove ships from collision boxes)

		//periodic tasks
		count++;
		if(count == PERIODIC){
			count = 0;
			for(int x = 0; x < importants.len; x++){//handles orphans and touching bubbles
				shipList[importants.list[x]]->tickImportant();
			}
		}
		//reset viewables
		for(int x = 0; x < importants.len; x++){
			shipList[importants.list[x]]->myBub->drawableCount = 0;
		}
		
		//tickShips (vel/rot changes based on controls, tick modules, advance ships, tick ais)
		for(int x = 0, shipsFound = 0; shipsFound < shipCount; x++){
			if(shipList[x] != NULL){
				shipsFound++;
				shipList[x]->tick();
			}
		}

		//wait Until time up.
		tickCount++;
		delay(FRAMERATE);
	}
}
void shutdown(){
}
