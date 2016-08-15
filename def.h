#define MSGSIZE 512
#define MAXUSERS 10
#define MAXSHIPS 100
#include "ship.h"
#include "user.h"
extern int sockfd;
extern User* userList[MAXUSERS];
extern int userCount;
extern Ship* shipList[MAXSHIPS];
extern int shipCount;
extern struct sockaddr_in recvAddr;
