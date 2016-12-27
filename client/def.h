#define CONTROLLERAXISMAX 32768.0
#define DEADZONE 8000
#define MSGSIZE 3000

#include "../share/dataTypes.h"
#include "../share/quatOps.h"
extern quat myRot;
extern quat targRot;
extern point myPos;
extern shipProto *shipTypes;
extern int has_joystick;
extern int sockfd;
extern struct sockaddr_in recvAddr, sendAddr;
