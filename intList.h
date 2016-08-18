#ifndef INTLIST_H
#define INTLIST_H
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
class IntList{
public:
	IntList();
	void add(int val);
	int *list = NULL;
	int len = 0;
	void remove(int idx);
	int search(int val);
	
};
#endif
