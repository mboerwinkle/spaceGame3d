#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "dataTypes.h"
#include "ship.h"
#include "user.h"
#include "ai.h"
#include "def.h"
#include "delay.h"
#include "netListen.h"
#include "readScenario.h"
#include "blockUnionProto.h"
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
shipProto* shipTypes;
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
void readData(){
	FILE* fp = fopen("ships.cfg", "r");
	if(fp == NULL){
		puts("FATAL: ships.cfg not found.");
	}
	int numShips;
	fscanf(fp, "%d", &numShips);
	shipTypes = (shipProto*)calloc(numShips, sizeof(shipProto));
	char blockUnionFile[80];
	for(int x = 0; x< numShips; x++){
		fscanf(fp, "%d %d %d %d %lf %lf %lf %s", &(shipTypes[x].maxSpeed),  &(shipTypes[x].accel),  &(shipTypes[x].decel), &(shipTypes[x].rad), &(shipTypes[x].rollAngle),  &(shipTypes[x].yawAngle),  &(shipTypes[x].pitchAngle),  blockUnionFile);
		if(strcmp("NONE", blockUnionFile)){
			shipTypes[x].myBlock = new BlockUnionProto(blockUnionFile);
		}else shipTypes[x].myBlock = NULL;
	}
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
		count++;
		if(count == PERIODIC){
			count = 0;
			for(int x = 0; x < importants.len; x++){//handles orphans and touching bubbles
				shipList[importants.list[x]]->tickImportant();
			}
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
