#ifndef MOD_LASER_H
#define MOD_LASER_H
#include "module.h"
class Module;
class ModLaser: public Module{
public:
	ModLaser(Ship* owner);
	~ModLaser();
	void tick(int stat);
	Ship* owner;
private:
	void fire();
	int maxCoolDown = 20;
	int coolDown = 0;//FIXME use a short?
};
#endif
