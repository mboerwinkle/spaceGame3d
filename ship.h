#ifndef SHIP_H
#define SHIP_H
#include "dataTypes.h"
#include "bubble.h"
#include "def.h"
class Bubble;
class Ship{
public:
	void tick();
	Ship(point pos, quat rot, int important, int* idx);

	controls ctl;
	int index;
	int important;
	Bubble* myBubble = NULL;
	
	int speed = 0;
	point pos = {500000,500000,500000};
	quat rot = {1,0,0,0};
private:
	void addSpeed();
};
extern Ship* shipList[MAXSHIPS];
extern int shipCount;
extern int orphans[MAXSHIPS];
extern int orphanCount;
#endif
