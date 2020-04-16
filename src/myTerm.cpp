#include "myTerm.h"

int mt_clrscr (void) {
    cout << "\033[H\033[H\033[2J";
    return 0;
}

int mt_gotoXY (int x, int y) {
    printf("\033[%d;%dH", x, y);
    return 0;
}

int mt_getscreensize(int *rows, int *cols) 
{
    struct winSize {
		unsigned short ws_row;
		unsigned short ws_col;
        unsigned short size_pix_x;
		unsigned short size_pix_y;
	} ws;
    
    if (!ioctl(1, TIOCGWINSZ, &ws)) {
        *rows=ws.ws_row;
        *cols=ws.ws_col;
        return 0;
    } else 
        return -1;
}


int mt_setfgcolor (enum colors color) {
    if ((int)color < 0 || (int)color > 7)
		return -1;
    printf("\033[3%dm", color);
    return 0;
}

int mt_setbgcolor (enum colors color) {
    if ((int)color < 0 || (int)color > 7)
		return -1;
    printf("\033[4%dm", color);
    return 0;
}
