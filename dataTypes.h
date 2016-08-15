#include <inttypes.h>
#ifndef DATATYPES_H
#define DATATYPES_H
typedef uint64_t point[3];
typedef double quat[4];
typedef struct controls{
	double accel;//0 - 1
	double yaw;//-1 - 1
	double roll;//-1 - 1
	double pitch;//-1 - 1
	int fire;
}controls;
#endif
