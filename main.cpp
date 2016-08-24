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
IntList orphans;
IntList importants;
struct sockaddr_in recvAddr;
unsigned int tickCount = 0;

static void makeEnvironment();

int main(){
	setupNetwork();
	makeEnvironment();
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
static void makeEnvironment(){
	int bogus;
	uint64_t pos[3] = {50000, 50000, 50000};
	double rot[4] = {1, 0, 0, 0};
	pos[0] = 50500;
	new Ship(pos, rot, 0, &bogus);
	pos[0] = 49500;
	new Ship(pos, rot, 0, &bogus);
	pos[0] = 50000;
	pos[1] = 50500;
	new Ship(pos, rot, 0, &bogus);
	pos[1] = 49500;
	new Ship(pos, rot, 0, &bogus);
	pos[1] = 50000;
	pos[2] = 50500;
	new Ship(pos, rot, 0, &bogus);
	pos[2] = 49500;
	new Ship(pos, rot, 0, &bogus);
	pos[2] = 50000;
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
		//FIXME dont need to tickImportants every tick
		for(int x = 0; x < importants.len; x++){//handles orphans and touching bubbles
			shipList[importants.list[x]]->tickImportant();
		}		
		//wait Until time up.
		tickCount++;
		delay(60);
	}
}
void shutdown(){
}
