#ifndef _MYTERM_H_
#define _MYTERM_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
using namespace std;

#define TERM "/dev/tty"

enum colors {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        VIOLET,
        BIRUZ,
        WHITE,
        DEFAULT = 9
};


int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor (enum colors);
int mt_setbgcolor (enum colors); 

#endif