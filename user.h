#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "def.h"
#ifndef USER_H
#define USER_H
class User{
public:
	User(unsigned long ip);
	struct sockaddr_in addr;
	int shipIdx = -1;//client sends signal to connect to a ship
	void sendUserData();
private:
};
extern User* userList[MAXUSERS];
extern int userCount;
#endif
