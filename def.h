#define MSGSIZE 512//size of udp data per packet
#define MAXUSERS 10//maximum amount of handleable users
#define MAXSHIPS 100//maximum amount of handleable ships
#define BUBBLERAD 5000//radius of collision bubbles
#define FRAMERATE 40
#define PERIODIC 40//how often things that dont need to happen every tick happen
extern int sockfd;
extern struct sockaddr_in recvAddr;
extern unsigned int tickCount;
