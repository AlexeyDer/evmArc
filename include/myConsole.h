#ifndef _MYCONSOLE_H_
#define _MYCONSOLE_H_

#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"

static int command;
static int operand;

#define STD_X_MEM 1
#define STD_Y_MEM 1
#define STD_DX_MEM 12
#define STD_DY_MEM 62

#define STD_X_ACC 1
#define STD_Y_ACC 63

static int pointer_mem;

void reset();
void visualMemory();
void visualAccumulator();
int visualCounter();
void visualFlags();
void visualMenu();
void visualOperation();
void visualBigCharArea();

#endif