#ifndef BUBBLE_H
#define BUBBLE_H
#include "dataTypes.h"
#include "def.h"
class Ship;
class Bubble{
public:
	Bubble(Ship *owner);
	void updateOrphans();
	int shipIdx[MAXSHIPS];//FIXME make dynamic
	int len = 0;
	Ship *owner;
private:
	void addOrphans();
	void makeOrphans();
};
#endif
