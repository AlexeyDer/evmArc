#include "../include/myConsole.h"
#include "../include/myTerm.h"
#include "../include/myBigChar.h"
#include "../include/mySimpleComputer.h"
#include "../include/myReadKey.h"
#include "../include/cpu.h"

int visual_access;
struct itimerval nval;

void settimer(struct itimerval *nval)
{
	nval->it_interval.tv_sec = 0;
	nval->it_interval.tv_usec = 0;
	nval->it_value.tv_sec = 0;
	nval->it_value.tv_usec = 200000;
}

void run(int siq)
{
	if (siq != SIGALRM)
	{
		return;
	}
	CU();
	++pointer_mem;
	if (pointer_mem == N)
	{
		pointer_mem = 0;
		sc_regSet(IGNOREPULSE, 0);
	}
	// sc_countSet(pointer_mem);
	instruction_counter = pointer_mem;
}

void reset(int siq)
{
	if (siq != SIGUSR1)
	{
		return;
	}
	sc_memoryInit();
	sc_regInit();
	// sc_countSet(0);
	instruction_counter = 0;
	setVisualNull();
}

int setVisualNull()
{
	visual_access = visual_access & 0;
	return 0;
}

int updateMemVisual()
{
	visualRegSet(MEM, 0);
	visualRegSet(ACC, 0);
	visualRegSet(OPER, 0);
	visualRegSet(BC, 0);
	visualRegSet(INSTR, 0);

	return 0;
}

void clrMessageBox(int x, int y)
{

	mt_setfgcolor(BLACK);
	for (int i = y; i < y + 50; i++)
	{
		mt_gotoXY(x + 1, i);
		bc_printA(" ");
	}

	mt_setfgcolor(WHITE);
	setVisualNull();
}

void setOperation()
{
	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

	mt_gotoXY(x, y);
	mt_setfgcolor(RED);
	printf("I");
	mt_gotoXY(x + 1, y);
	mt_setfgcolor(WHITE);
	printf(":");
	mt_gotoXY(x + 1, y + 1);
	mt_setbgcolor(BLACK);

	int command, operand;

	printf(" Command and Operand: ");
	fscanf(stdin, "%d", &command);
	fscanf(stdin, "%d", &operand);
	int value;
	sc_commandEncode(command, operand, &value);

	if (value > 0)
		value = value & 0x3fff;
	else
	{
		value--;
		value = ~value;
		value = value | (0x1 << 14);
	}

	accumulator = value;
	sc_memorySet(pointer_mem, value);

	mt_setbgcolor(BLACK);
	clrMessageBox(x, y);
	setVisualNull();
}

void setPointer()
{
	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

	mt_gotoXY(x, y);
	mt_setfgcolor(RED);
	printf("I");
	mt_gotoXY(x + 1, y);
	mt_setfgcolor(WHITE);
	printf(":");
	mt_gotoXY(x + 1, y + 1);
	mt_setbgcolor(BLACK);

	int ptr;
	fscanf(stdin, "%d", &ptr); //
	if (-1 < ptr && ptr < N)
		pointer_mem = ptr;
	else
		sc_regSet(ERRORADD, 1);
	mt_setbgcolor(BLACK);
	clrMessageBox(x, y);
	setVisualNull();
}

void setAcc()
{
	FILE *f = fopen("globalht.txt", "at");
	putc('Y', f);
	fclose(f);

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

	mt_gotoXY(x, y);
	mt_setfgcolor(RED);
	printf("I");
	mt_gotoXY(x + 1, y);
	mt_setfgcolor(WHITE);
	printf(":");
	mt_gotoXY(x + 1, y + 1);
	mt_setbgcolor(BLACK);

	int value;
	fscanf(stdin, "%x", &value); //
	if (value > 0)
		value = value & 0x3fff;
	else
	{
		value--;
		value = ~value;
		value = value | (0x1 << 14);
	}
	// sc_accumSet(value);
	accumulator = value;
	sc_memorySet(pointer_mem, value);
	mt_setbgcolor(BLACK);
	clrMessageBox(x, y);
	setVisualNull();
}

int visualRegSet(int flag, int value)
{
	if (0 <= flag && flag < 32)
	{
		if (value == 0)
			visual_access = visual_access & (~(1 << flag));
		else if (value == 1)
			visual_access = visual_access | (1 << flag);
		else
			return -1;
		return 0;
	}
	sc_regSet(ERRORFLAG, 1);
	return ERRORFLAG;
}

int visualRegGet(int flag, int *value)
{
	if (-1 < flag && flag < 32)
	{
		*value = (visual_access >> flag) & 0x1;
		return 0;
	}
	sc_regSet(ERRORFLAG, 1);
	return ERRORFLAG;
}

//Visual

void showAll()
{

	visualInOut();
	visualMemory();
	visualAccumulator();
	visualCounter();
	visualOperation();
	visualFlags();
	visualMenu();
	visualBigCharArea();

	fflush(stdout);
	mt_gotoXY(1, 1);
}

void visualInOut()
{
	int value;
	visualRegGet(IO, &value);
	if (value)
		return;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM + 10, y = m / 4;
	int dx = 3, dy = 87;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);

	bc_box(x, y, dx, dy);

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	mt_gotoXY(x, y + 1);
	printf(" Input / Output");

	mt_setbgcolor(DEFAULT);

	mt_gotoXY(x + 1, y + 21);

	visualRegSet(IO, 1);
}

void visualMemory()
{

	int value;
	int k = 2;
	visualRegGet(MEM, &value);

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3, y = m / 4;
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
	visualRegSet(MEM, 1);
}

void visualAccumulator()
{
	int value;
	visualRegGet(ACC, &value);
	if (value)
		return;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3, y = m / 4 + STD_DY_MEM + 3;
	int dx = 3, dy = 22;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	bc_box(x, y, dx, dy);
	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);

	mt_gotoXY(x, y + 5);
	printf(" accumulator ");

	mt_setbgcolor(BLACK);
	mt_gotoXY(x + 1, y + 8);
	// sc_accumGet(&value);
	value = accumulator;
	value = (value & 0x3fff);
	if ((value >> 14))
	{
		printf("-%04X", value);
	}
	else
	{
		printf("+%04X", value);
	}
	visualRegSet(ACC, 1);
}

int visualCounter()
{
	int value;
	visualRegGet(INSTR, &value);

	if (value)
		return 0;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + 3, y = m / 4 + STD_DY_MEM + 3;
	int dx = 3, dy = 22;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	bc_box(x, y, dx, dy);
	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);

	mt_gotoXY(x, y + 1);
	printf(" instructionCounter ");
	mt_setbgcolor(BLACK);
	mt_gotoXY(x + 1, y + 8);
	printf("+%04X", pointer_mem);
	visualRegSet(INSTR, 1);
	return 0;
}

void visualOperation()
{
	int command = 0, operand = 0;
	int value;
	visualRegGet(OPER, &value);
	if (value)
		return;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + 6, y = m / 4 + STD_DY_MEM + 3;
	int dx = 3, dy = 22;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	bc_box(x, y, dx, dy);
	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	mt_gotoXY(x, y + 5);
	printf(" Operation ");

	sc_memoryGet(pointer_mem, &value);
	sc_commandDecode(value, &command, &operand);

	mt_setbgcolor(BLACK);
	mt_gotoXY(x + 1, y + 6);
	printf("+ %02X : %02X", command, operand);

	visualRegSet(OPER, 1);
}

void visualFlags()
{

	int value;
	visualRegGet(FLAGS, &value);
	if (value)
		return;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + 9, y = m / 4 + STD_DY_MEM + 3;
	int dx = 3, dy = 22;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	bc_box(x, y, dx, dy);
	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	mt_gotoXY(x, y + 7);
	printf(" Flags ");

	mt_gotoXY(x + 1, y + 7);

	sc_regGet(ERRORADD, &value);
	if (value)
	{
		printf("A");
	}

	sc_regGet(ERRORFLAG, &value);
	if (value)
	{
		printf("  F");
	}

	sc_regGet(ERRORFILE, &value);
	if (value)
	{
		printf("    D");
	}

	sc_regGet(ERRORCOMS, &value);
	if (value)
	{
		printf("      C");
	}

	sc_regGet(IGNOREPULSE, &value);
	if (value)
	{
		printf("        T");
	}

	visualRegSet(FLAGS, 1);
}

void visualMenu()
{
	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM, y = m / 4 + 50;
	int dx = 10, dy = 37;

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
	visualRegGet(BC, &value);
	if (value)
		return;

	int n, m;
	mt_getscreensize(&n, &m);
	int x = n / 3 + STD_DX_MEM, y = m / 4;
	int dx = 10, dy = 49;

	mt_setfgcolor(WHITE);
	mt_setbgcolor(BLACK);
	bc_box(x, y, dx, dy);

	int big[2] = {0, 0};
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
