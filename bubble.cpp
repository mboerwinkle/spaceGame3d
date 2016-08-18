#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "def.h"
#include "bubble.h"
#include "chebDist.h"
Bubble::Bubble(Ship* owner){
	this->owner = owner;
	shipIdx.add(owner->index);	
}
void Bubble::updateOrphans(){
	addOrphans();
	makeOrphans();
}
void Bubble::addOrphans(){
	for(int x = 0; x < orphans.len; x++){
		if(chebDist(shipList[orphans.list[x]], owner) < BUBBLERAD){
			shipIdx.add(orphans.list[x]);
			orphans.remove(x);
			shipList[shipIdx.list[shipIdx.len-1]]->myBubble = this;
		}
	}
}
void Bubble::makeOrphans(){
	for(int x = 1; x < shipIdx.len; x++){
		if(chebDist(shipList[shipIdx.list[x]], owner) > BUBBLERAD){
			orphans.add(shipIdx.list[x]);
			shipIdx.remove(x);
			shipList[orphans.list[orphans.len-1]]->myBubble = 0;
		}
	}
}
