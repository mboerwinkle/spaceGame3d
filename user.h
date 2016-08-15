#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "ship.h"
#ifndef USER_H
#define USER_H
class User{
public:
	User(unsigned long ip);
	struct sockaddr_in addr;
	Ship* view = NULL;//client sends signal to connect to a ship
	void sendUserData();
private:
};
#endif
