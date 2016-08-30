#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "def.h"
#include "netParse.h"
#include "gfx.h"
#include "events.h"

controls ctls;
int sockfd;
struct sockaddr_in recvAddr, sendAddr;
void startNetwork(char* ip, int port);
void handleNetwork();
char localhost[10] = "127.0.0.1";
point myPos;
quat myRot;
int main(int argc, char** argv){
	if(argc == 1){
		startNetwork(localhost, 5999);
	}else if(argc == 2){
		startNetwork(argv[1], 5999);
//	}else if(argc == 3) {
//		startNetwork(argv[1], atoi(argv[2]));
	}else{
		puts("Usage: ./cli.out [server ip]");
	}
	initGfx();
	while(1){
		handleNetwork();
		if(handleEvents()){
			break;
		}
	}
	//send disconnect msg to server
	quitGfx();
	return 0;
}
void startNetwork(char* ip, int port){
	if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) {
		puts("Couldn't get socket!!!");
	}

	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(6000);
	inet_aton(ip, &sendAddr.sin_addr);

	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(port);
	recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr))) {
		puts("Couldn't listen for things!");
	}
	char alert[] = "joining\0";
	sendto(sockfd, alert, sizeof(alert), 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
	sendto(sockfd, "SPN\0", sizeof("SPN\0"), 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
}
void handleNetwork(){
	//Don't really want something potentially large on the stack, therefore static
	static char msg[MSGSIZE];
	int len = recvfrom(sockfd, msg, MSGSIZE, 0, NULL, NULL);
	netParse(msg, len);
}
