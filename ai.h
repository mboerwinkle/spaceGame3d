#include "def.h"
#ifndef AI_H
#define AI_H
class AI{
public:
	AI(int shipIdx);
	int shipIdx;
	int important;
	void tick();
private:
};
extern AI* aiList[MAXSHIPS];
extern int aiCount;
#endif
