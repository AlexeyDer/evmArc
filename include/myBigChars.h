#ifndef _MYBIGCHARS_H_
#define _MYBIGCHARS_H_

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "mySimpleComputer.h"
#include "myTerm.h"

#define upleft "l"
#define upright "k"
#define horiz "q"
#define vert "x"
#define downleft "m"
#define downright "j"

#define ACS_CKBOARD "a"
#define BC_SIZE_DEFAULT 2
static int BC_SIZE;

extern enum colors color;

int bc_printA(char* str);
int bc_box(int x, int y, int dx, int dy);
int bc_printbigchar(unsigned int[], int, int, enum colors, enum colors);
int bc_setbigcharpos(unsigned int*, int, int, int);
int bc_getbigcharpos(unsigned int*, int, int, int*);
int bc_bigcharwrite(int, unsigned int*, int);
int bc_bigcharread(int, unsigned int*, int, int*); 
int bc_initBigChar(unsigned int*, char); 

#endif