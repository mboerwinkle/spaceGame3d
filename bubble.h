#ifndef BUBBLE_H
#define BUBBLE_H
#include "dataTypes.h"
#include "def.h"
#include "intList.h"
class Ship;
class Bubble{
public:
	Bubble(Ship *owner);
	~Bubble();
	void assignTasks();
	void updateOrphans();
	IntList shipIdx;
	IntList closeImportant;
	Ship *owner;
private:
	void addOrphans();
	void makeOrphans();
};
#endif
