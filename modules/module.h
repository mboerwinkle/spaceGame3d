#ifndef MODULE_H
#define MODULE_H
class Ship;
class Module{
public:
	virtual ~Module() = 0;
	virtual void tick(int stat) = 0;
	Ship* owner;
};
/*include other module .h files here*/
#include "modLaser.h"
#endif
