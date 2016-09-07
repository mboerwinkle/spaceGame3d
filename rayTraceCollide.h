#include "ship.h"
#include "bubble.h"
#include "dataTypes.h"
extern Ship* rayTraceCollide(Bubble* whichBubble, point origin, quat dir, uint64_t* mindist);//for vector origin, dir: checks if any ship inside of whichBubble or any connected bubbles intersects the vector. If it does, sets type to a specifier of what type of object, hit is a pointer to the object, and returns distance to intersection. Else, hit is set to NULL.
