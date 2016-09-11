#ifndef GFX_H
#define GFX_H

#include "dataTypes.h"

extern void drawShip(short type, point where, quat rot);

extern void gfxClear();

extern void gfxFlip();

extern void initGfx();

extern void quitGfx();

#endif
