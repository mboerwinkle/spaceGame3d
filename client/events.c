#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <SDL2/SDL.h>
#include "dataTypes.h"
#include "def.h"

int spKeyAction(SDL_Keycode key, int pressed){
	switch(key){
		case SDLK_w://accelerate
			ctls.accel = pressed;
			return 1;
		case SDLK_a:
			ctls.roll = pressed;
			return 1;
		case SDLK_s:
			ctls.accel = -pressed;
			return 1;
		case SDLK_d:
			ctls.roll = -pressed;
			return 1;
		case SDLK_UP:
			ctls.pitch = pressed;
			return 1;
		case SDLK_LEFT:
			ctls.yaw = -pressed;
			return 1;
		case SDLK_DOWN:
			ctls.pitch = -pressed;
			return 1;
		case SDLK_RIGHT:
			ctls.yaw = pressed;
			return 1;
		default:
			return 0;
	}
}

int handleEvents(){
	int send = 0;//if controls need to be sent
	static SDL_Event evnt;
	while(SDL_PollEvent(&evnt)){
		if(evnt.type == SDL_QUIT){
			return 1;
		}
		else if(evnt.type == SDL_KEYDOWN){
			if(spKeyAction(evnt.key.keysym.sym, 1)) send = 1;
		}
		else if(evnt.type == SDL_KEYUP){
			if(spKeyAction(evnt.key.keysym.sym, 0)) send = 1;
		}
	}
	if(send){
		//send controls to server
		char msg[3+sizeof(controls)] = "CTL";
		memcpy(msg+3, &ctls, sizeof(controls));
		sendto(sockfd, msg, 3+sizeof(controls), 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
	}
	return 0;
}


