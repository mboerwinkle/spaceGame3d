#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "def.h"
#include "bubble.h"
#include "chebDist.h"
Bubble::Bubble(Ship* owner){
	len = 1;
	this->owner = owner;
	shipIdx[0] = owner->index;	
}
void Bubble::updateOrphans(){
	addOrphans();
	makeOrphans();
}
void Bubble::addOrphans(){
	for(int x = 0; x < orphanCount; x++){
		if(chebDist(shipList[orphans[x]], owner) < BUBBLERAD){
			shipIdx[len] = orphans[x];
			orphans[x] = 0;
			shipList[shipIdx[len]]->myBubble = this;
			len++;
		}
	}
}
void Bubble::makeOrphans(){
	for(int x = 1; x < len; x++){
		if(chebDist(shipList[shipIdx[x]], owner) > BUBBLERAD){
			orphans[orphanCount] = shipIdx[x];
			shipIdx[x] = 0;
			shipList[orphans[orphanCount]]->myBubble = 0;
			orphanCount++;
		}
	}
}
