#include <inttypes.h>
#ifndef DATATYPES_H
#define DATATYPES_H
class BlockUnionProto;
typedef uint64_t point[3];
typedef int64_t signedPoint[3];//used for relative comparisons only
typedef double quat[4];//real is first (w, x, y, z)
typedef struct controls{
	double accel = 0;//0 - 1
	double yaw = 0;//-1 - 1
	double roll = 0;//-1 - 1
	double pitch = 0;//-1 - 1
	int fire = 0;//this limits to 32 modules. doesnt really seem like a limit.
}controls;
typedef struct shipProto{
	int maxSpeed;
	int accel;
	int decel;
	int rad;
	double rollAngle;
	double yawAngle;
	double pitchAngle;
	BlockUnionProto* myBlock;
}shipProto;
extern shipProto* shipTypes;
#endif
