#include "myConsole.h"

int main()
{
  int value;
  mt_clrscr();

  pointer_mem = 0;
  reset();
  visualMemory();
  visualAccumulator();
  visualCounter();
  visualOperation();
  visualFlags();
  visualMenu();
  visualBigCharArea();

  mt_gotoXY(30, 1);

  return 0;
}