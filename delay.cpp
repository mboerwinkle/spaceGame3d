#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
struct timespec t = {.tv_sec=0};
struct timespec lastTime = {.tv_sec=0, .tv_nsec = 0};
struct timespec otherTime = {.tv_sec = 0, .tv_nsec=0};
void delay(int fps){
	clock_gettime(CLOCK_MONOTONIC, &otherTime);
	int32_t sleep = (int32_t)(1000000000/fps)-(otherTime.tv_nsec-lastTime.tv_nsec)-1000000000l*(otherTime.tv_sec-lastTime.tv_sec);
	if(sleep>0){
		t.tv_nsec = sleep;
		nanosleep(&t, NULL);
	}else{
		puts("tick's computations took more than allotted time");
	}
	clock_gettime(CLOCK_MONOTONIC, &lastTime);
}
