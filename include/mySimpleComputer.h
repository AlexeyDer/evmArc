#ifndef _MYSIMPLECOMPUTER_H_
#define _MYSIMPLECOMPUTER_H_

#include <stdlib.h>
#include <iostream>
using namespace std;

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5

static int a[100];
static int flag;

void printMemory();
int printFlag(int flag);

int sc_memoryInit ();
int sc_memorySave(char *filename);
int sc_memorySet(int address, int value);
int sc_memoryGet (int address, int *value);

int sc_memorySave(char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit (void);
int sc_regSet (int register, int value);
int sc_regGet (int register, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode (int value, int *command,int *operand);

#endif



