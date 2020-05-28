#ifndef MYCONSOLE_H
#define MYCONSOLE_H

#include "cpu.h"
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

extern struct itimerval nval;

void settimer(struct itimerval *nval);

#define STD_X_MEM 1
#define STD_Y_MEM 1
#define STD_DX_MEM 12
#define STD_DY_MEM 62

#define STD_X_ACC 1
#define STD_Y_ACC 63

#define MEM 0
#define ACC 1
#define INSTR 2
#define OPER 3
#define KEYS 4
#define BC 5
#define IO 6
#define FLAGS 7

extern int visual_access;

//Console part
void reset(int siq);
void run(int siq);

int setVisualNull();

int updateMemVisual();
int visualRegGet(int flag, int *value);
int visualRegSet(int flag, int value);

void setAcc();
void setPointer();
void setOperation();

void clrMessageBox(int x, int y);

//Visual part
void showAll();
void visualInOut();
void visualMemory();
void visualAccumulator();
int visualCounter();
void visualOperation();
void visualFlags();
void visualMenu();
void visualBigCharArea();

#endif