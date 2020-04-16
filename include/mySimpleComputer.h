#ifndef _MYSIMPLECOMPUTER_H_
#define _MYSIMPLECOMPUTER_H_

#include <stdlib.h>
#include <iostream>
using namespace std;

#define N 100
#define M 10

#define ERROROUTOFMEMORY 1
#define ERRORFLAG 2
#define ERRORFILE 3
#define ERRORCOMS 4
#define ERROROPER 5

static int a[100];
static int flag;

void printMemory();
int printFlag(int flag);

int sc_memoryInit();
int sc_memorySave(char *filename);
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);

int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);

int sc_regInit(void);
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

int sc_accumGet(int *value);

int sc_accumSet(int value);

int sc_countGet(int *value);

int sc_countSet(int value);

int sc_countInkrement();

int mt_clrscr(void);

#endif
