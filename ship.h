#ifndef SHIP_H
#define SHIP_H
#include "dataTypes.h"
#include "bubble.h"
#include "def.h"
#include "intList.h"
class Bubble;
class Ship{
public:
	void tick();
	void tickImportant();
	Ship(point pos, quat rot, int important, int* idx);

	controls ctl;
	int maxSpeed = 0;
	int accel = 10;
	int decel = 10;
	int index;
	int important;
	Bubble* myBubble = NULL;
	
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
