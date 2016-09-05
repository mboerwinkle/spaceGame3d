#include "../ship.h"
#include "module.h"
Module::~Module(){
	int good = 0;
	for(int x = 0; x < MAXMODULES; x++){
		if(owner->myMod[x] == this){
			owner->myMod[x] = NULL;
			good = 1;
			break;
		}
	}
	if(!good) puts("another fatal module error");
}
