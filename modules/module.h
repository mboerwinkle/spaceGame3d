#ifndef MODULE_H
#define MODULE_H
/*include other module .h files here*/
class Ship;
class Module{
public:
	virtual ~Module() = 0;
	virtual void tick(int stat) = 0;
	Ship* owner;
};
#endif
