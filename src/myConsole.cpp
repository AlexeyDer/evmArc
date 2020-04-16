#include "myConsole.h"

void reset()
{
    sc_memoryInit();
    sc_regInit();
    sc_countSet(0);
}

void visualMemory()
{
    int value;
    int k = 2;

    int x = 2, y = 2;
    int dx = STD_DX_MEM, dy = STD_DY_MEM + 1;

    bc_box(x, y, dx, dy);

    mt_gotoXY(x, y + STD_DY_MEM / 2 - 4);
    printf("Memory");

    for (int i = 0, j = 1; i < N; i++)
    {
        if (!(i % M))
        {
            mt_gotoXY(x + j++, y + 2);
        }

        mt_setfgcolor(WHITE);
        mt_setbgcolor(BLACK);
        if (pointer_mem == i)
        {
            mt_setfgcolor(BLACK);
            mt_setbgcolor(WHITE);
        }

        sc_memoryGet(i, &value);
        if ((value >> 14))
        {
            value = value & 0x3fff;
            printf("-%04X ", value);
        }
        else
        {
            printf("+%04X ", value);
        }
        if ((i + 1) % 10 == 0)
        {
            k++;
            mt_gotoXY(k, 2);
        }
    }
    mt_gotoXY(30, 1);
}

void visualAccumulator()
{
    int value;

    int x = 2, y = 2 + STD_DY_MEM + 1;
    int dx = 3, dy = 15;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    mt_gotoXY(x, y + 1);
    printf(" accumulator ");

    mt_setbgcolor(BLACK);
    mt_gotoXY(x + 1, y + 4);
    sc_accumGet(&value);
    value = (value & 0x3fff);
    if ((value >> 14))
    {
        printf("-%04X", value);
    }
    else
    {
        printf("+%04X", value);
    }
}

int visualCounter()
{
    int value;

    int x = 2 + 3, y = 2 + STD_DY_MEM + 1;
    int dx = 3, dy = 15;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    mt_gotoXY(x, y + 1);
    printf(" instruction ");
    mt_setbgcolor(BLACK);
    mt_gotoXY(x + 1, y + 4);
    printf("+%04X", pointer_mem);

    return 0;
}

void visualOperation()
{
    int value;

    int x = 2 + 6, y = 2 + STD_DY_MEM + 1;
    int dx = 3, dy = 15;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    mt_gotoXY(x, y + 2);
    printf(" Operation ");

    sc_memoryGet(pointer_mem, &value);
    sc_commandDecode(a[pointer_mem], &command, &operand);

    mt_setbgcolor(BLACK);
    mt_gotoXY(x + 1, y + 3);
    printf("+ %02X : %02X", command, operand);
}

void visualFlags()
{
    int value;

    int x = 2 + 9, y = 2 + STD_DY_MEM + 1;
    int dx = 3, dy = 15;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    mt_gotoXY(x, y + 3);
    printf(" Flags ");

    mt_gotoXY(x + 1, y + 2);

    sc_regGet(ERROROUTOFMEMORY, &value);
    if (!value)
    {
        printf("A");
    }

    sc_regGet(ERRORFLAG, &value);
    if (!value)
    {
        printf("  F");
    }

    sc_regGet(ERRORFILE, &value);
    if (!value)
    {
        printf("  D");
    }

    sc_regGet(ERRORCOMS, &value);
    if (!value)
    {
        printf("  C");
    }
}

void visualMenu()
{
    int x = 2 + STD_DX_MEM, y = 2 + 50;
    int dx = 10, dy = 27;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);
    mt_gotoXY(x, y + 1);
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    printf(" Keys: ");
    mt_setbgcolor(BLACK);
    mt_gotoXY(x + 1, y + 2);
    printf("L  - load");
    mt_gotoXY(x + 2, y + 2);
    printf("S  - save");
    mt_gotoXY(x + 3, y + 2);
    printf("R  - run");
    mt_gotoXY(x + 4, y + 2);
    printf("T  - step");
    mt_gotoXY(x + 5, y + 2);
    printf("I  - reset");
    mt_gotoXY(x + 6, y + 2);
    printf("A - accumulator");
    mt_gotoXY(x + 7, y + 2);
    printf("C - instructionCounter");
    mt_gotoXY(x + 8, y + 2);
    printf("Press \"Q\" to exit.");
}

void visualBigCharArea()
{
    int value;

    int x = 2 + STD_DX_MEM, y = 2;
    int dx = 10, dy = 49;

    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);
    bc_box(x, y, dx, dy);

    unsigned int big[2] = {0, 0};
    char ss[8];

    sc_memoryGet(pointer_mem, &value);
    if ((value >> 14))
    {
        value = value & 0x3fff;
        sprintf(ss, "-%04X", value);
    }
    else
    {
        sprintf(ss, "+%04X", value);
    }

    for (int i = 0; i < 5; i++)
    {
        bc_initBigChar(big, ss[i]);
        bc_printbigchar(big, x + 1, y + 2 + i * 9, BLACK, WHITE);
    }
}
