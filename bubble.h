#ifndef BUBBLE_H
#define BUBBLE_H
#include "share/dataTypes.h"
#include "def.h"
#include "share/intList.h"
#define MAXDRAWABLES 1000
class Ship;
class Bubble{
public:
	Bubble(Ship *owner);
	~Bubble();
	void assignTasks();
	void updateOrphans();
	int drawableCount = 0;
	drawable drawables[MAXDRAWABLES];//why make it dynamic when it could be non dynamic!
	IntList shipIdx;
	IntList closeImportant;
	Ship *owner;
private:
	void addOrphans();
	void makeOrphans();
};
#endif
