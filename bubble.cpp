#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "def.h"
#include "ai.h"
#include "bubble.h"
#include "share/chebDist.h"
Bubble::Bubble(Ship* owner){
	this->owner = owner;
	shipIdx.add(owner->index);	
}
Bubble::~Bubble(){
	for(int x = 1; x < shipIdx.len; x++){//FIXME go ahead and try to give them to closeImportant
			orphans.add(shipIdx.list[x]);
			shipList[orphans.list[orphans.len-1]]->myImp = -1;
	}
}
void Bubble::updateOrphans(){
	addOrphans();
	makeOrphans();
}
void Bubble::addOrphans(){
	for(int x = 0; x < orphans.len; x++){
		if(chebDist(shipList[orphans.list[x]]->pos, owner->pos) < BUBBLERAD){
			shipIdx.add(orphans.list[x]);
			orphans.remove(x);
			shipList[shipIdx.list[shipIdx.len-1]]->myImp = this->owner->index;//FIXME is this even stable?
			x--;//FIXME could I get some validation on this fix?
		}
	}
}
void Bubble::makeOrphans(){
	for(int x = 1; x < shipIdx.len; x++){
		if(chebDist(shipList[shipIdx.list[x]]->pos, owner->pos) > BUBBLERAD){
			orphans.add(shipIdx.list[x]);
			shipIdx.remove(x);
			shipList[orphans.list[orphans.len-1]]->myImp = -1;
			x--;//and here too
		}
	}
}
void Bubble::assignTasks(){
	Ship* currShip;
	for(int x = 0; x < shipIdx.len; x++){
		currShip = shipList[shipIdx.list[x]];
		if(currShip->myAI == NULL) continue;//does not have an AI.
		if(currShip->myAI->objective != -1) continue;//already has an objective
		//assign
	}
}
