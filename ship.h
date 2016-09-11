#ifndef SHIP_H
#define SHIP_H
#include <math.h>
#include "dataTypes.h"
#include "modules/module.h"
#include "ai.h"
#include "bubble.h"
#include "def.h"
#include "intList.h"
#include "blockUnionProto.h"
class Module;
class Bubble;
class Ship{
public:
	void tick();
	void tickImportant();
	Ship(short type, point pos, quat rot, int important, int* idx);
	~Ship();

	controls ctl;
	short team = 1;//if (ship1.team)&(ship2.team), then dont attack
	short shipType;
	int maxSpeed;
	int accel;
	int decel;
	double rollAngle;//in radians
	double yawAngle;
	double pitchAngle;
	int index;
	int important;
	Bubble* myBub = NULL;//if this ship is important, this is a pointer to its bubble. otherwise unused.
	int myImp = -1;//if this ship is important, unused. otherwise is the index of the ship whose bubble I am in.
	AI* myAI = NULL;
	Module *myMod[MAXMODULES];
	BlockUnionProto* myBlock = NULL;
	//
	
	int rad;
	int speed = 0;
	point pos = {500000,500000,500000};
	quat rot = {1,0,0,0};
private:
	void addSpeed();
	void applyControls();
};
extern Ship* shipList[MAXSHIPS];
extern int shipCount;
extern IntList importants;
extern IntList orphans;
#endif
