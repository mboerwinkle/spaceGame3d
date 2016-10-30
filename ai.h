#include "ship.h"
#include "def.h"
#ifndef AI_H
#define AI_H
class Ship;
class AI{
public:
	AI(int shipIdx);
	~AI();
	int objective = 2;
	int shipIdx;
	point objLoc = {504000, 500000, 500000};//coord of objective, if required
//	int homeShipIdx;//this might be useful for cheating miners
	point home;//this is not cheating
	int objIdx;//index of objective, if required
	void tick();
private:
	int go(point loc);//these subroutines usually return info as to their completion
	int attack(Ship* targ);
	void circle(point loc, int rad);
	//void mine(point loc);//Maybe something like: go to this location, if there are any asteroids near mine till sated, return to point home and set objective to -1
};
#endif
