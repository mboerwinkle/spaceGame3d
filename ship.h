#include "dataTypes.h"
#ifndef SHIP_H
#define SHIP_H
class Ship{
public:
	void tick();
	Ship(point pos, quat rot, int important);

	controls ctl;
	int index;//FIXME
	int important;//controls whether or not they are expected to required to 
	
	int speed = 1;
	point pos = {500000,500000,500000};
	quat rot = {1,0,0,0};
private:
	void addSpeed();
};
#endif
