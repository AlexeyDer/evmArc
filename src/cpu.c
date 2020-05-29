#include "../include/cpu.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include "../include/myConsole.h"

int ALU(int command, int operand)
{
    if (operand > 99)
    {
        return 1;
    }

    switch (command)
    {
    case ADD:
        if ((accumulator + memory[operand]) >= 65535)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator += memory[operand];
        break;
    case SUB:
        if ((accumulator - memory[operand]) < -65534)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator -= memory[operand];
        break;
    case DIVIDE:
        if (memory[operand] == 0 || accumulator == 0)
        {
            sc_regSet(DE, 1);
            break;
        }
        accumulator /= memory[operand];
        break;
    case MUL:
        if ((accumulator * memory[operand]) >= 65535)
        {
            sc_regSet(OD, 1);
            break;
        }
        accumulator *= memory[operand];
        break;
    default:
        return 1;
    }

    return 0;
}

int CU(void)
{
    int value;
    int command, operand;

    sc_memoryGet(pointer_mem, &value);
    if (sc_commandDecode(value, &command, &operand))
    {
        sc_regSet(ERRORFLAG, 1);
        return 1;
    }

    value = 0;

    if (command < 30 || command > 33)
    {
        switch (command)
        {
        case READ:
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

            int value;
            fscanf(stdin, "%x", &value);

            if (value > 65535)
            {
                sc_regSet(ERRORADD, 1);
                break;
            }

            sc_memorySet(operand, value);

            mt_setbgcolor(BLACK);
            clrMessageBox(x, y);
            setVisualNull();
        }
        break;
        case WRITE:
        {
            int n, m;
            mt_getscreensize(&n, &m);
            int x = n / 3 + STD_DX_MEM + 10, y = m / 4 + 2;

            mt_gotoXY(x, y + 8);
            mt_setfgcolor(RED);
            printf("O");
            mt_gotoXY(x + 1, y);
            mt_setfgcolor(WHITE);
            printf(":");

            mt_gotoXY(x + 1, y + 1);
            mt_setbgcolor(BLACK);

            sc_memoryGet(operand, &value);
            printf("%02x", value);
            getchar();
            break;
        }
        case LOAD:
            sc_memoryGet(operand, &accumulator);
            break;
        case STORE:
        {
            sc_memorySet(operand, accumulator);
            break;
        }
        case JUMP:
            if (operand > 99 || operand < 0)
            {
                sc_regSet(EG, 1);
                break;
            }
            pointer_mem = --operand;
            break;
        case JNEG:
            if (accumulator < 0)
            {
                if (operand > 99 || operand < 0)
                {
                    sc_regSet(EG, 1);
                    break;
                }
                pointer_mem = --operand;
            }
            break;
        case JZ:
            if (accumulator == 0)
            {
                if (operand > 99 || operand < 0)
                {
                    sc_regSet(EG, 1);
                    break;
                }
                pointer_mem = --operand;
            }
            break;
        case JNS:
            if (accumulator >= 0)
            {
                if (operand > 99 || operand < 0)
                {
                    sc_regSet(EG, 1);
                    break;
                }
                pointer_mem = --operand;
            }
            break;
        case SET:
            accumulator = operand;
            break;
        case HALT:
            sc_regSet(IGNOREPULSE, 0);
            return 2;
            break;
        default:
            break;
        }
    }
    else
    {
        if (ALU(command, operand))
        {
            return 1;
        }
    }

    return 0;
}
