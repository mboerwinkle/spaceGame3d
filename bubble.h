#ifndef BUBBLE_H
#define BUBBLE_H
#include "dataTypes.h"
#include "def.h"
#include "intList.h"
class Ship;
class Bubble{
public:
	Bubble(Ship *owner);
	void updateOrphans();
	IntList shipIdx;
	int len = 0;
	Ship *owner;
private:
	void addOrphans();
	void makeOrphans();
};
#endif
