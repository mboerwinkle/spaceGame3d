#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "def.h"

int sockfd;
struct sockaddr_in recvAddr, sendAddr;
void startNetwork(char* ip);
void handleNetwork();
int main(int argc, char** argv){
	if(argc != 2){
		puts("put ip");
		return 1;
	}
	startNetwork(argv[1]);
	while(1){
		handleNetwork();
	}
	return 0;
}
void startNetwork(char* ip){
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	sendAddr.sin_family = AF_INET;
	sendAddr.sin_port = htons(6000);
	inet_aton(ip, &sendAddr.sin_addr);

	recvAddr.sin_family = AF_INET;
	recvAddr.sin_port = htons(5999);
	recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr));
	sendto(sockfd, "joining\0", sizeof("joining\0"), 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
}
void handleNetwork(){
	char msg[MSGSIZE];
	recvfrom(sockfd, msg, MSGSIZE, 0, NULL, NULL);
	printf("%s\n", msg);
}
